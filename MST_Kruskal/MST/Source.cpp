#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct Vertices
{
	unsigned id;
	char name[9];
	unsigned color;
};

struct Edges
{
	unsigned id_vertex1;
	unsigned id_vertex2;
	unsigned weight;
};

void fillArrays(std::vector<Vertices>&, std::vector<Edges>&);
void sort(std::vector<Edges>&);
void swapStructs(Edges&, Edges&);
unsigned findIndexByVertId(const std::vector<Vertices>&, unsigned);
void setColor(std::vector<Vertices>&, unsigned, unsigned);
void makeMST(std::vector<Vertices>&, std::vector<Edges>&);
void printData(const std::vector<Vertices>&, const std::vector<Edges>&);

int main()
{
	std::vector<Vertices> vertices_array;
	std::vector<Edges> edges_array;

	fillArrays(vertices_array, edges_array);
	sort(edges_array);

	makeMST(vertices_array, edges_array);

	printData(vertices_array, edges_array);
	return 0;
}

void fillArrays(std::vector<Vertices>& vertices_array, std::vector<Edges>& edges_array)
{
	Vertices vert_obj;

	unsigned nr_of_vertices;
	cin >> nr_of_vertices;

	for (unsigned i = 0; i < nr_of_vertices; i++)
	{
		cin >> vert_obj.id >> vert_obj.name;
		vert_obj.color = vert_obj.id;
		vertices_array.push_back(vert_obj);
	}

	Edges edge_obj;

	unsigned nr_of_edges;
	cin >> nr_of_edges;

	for (unsigned i = 0; i < nr_of_edges; i++)
	{
		cin >> edge_obj.id_vertex1 >> edge_obj.id_vertex2 >> edge_obj.weight;
		edges_array.push_back(edge_obj);
	}
}


void sort(std::vector<Edges>& edges_array)
{
	for (unsigned i = 0; i < edges_array.size() - 1; i++)
	{
		for (unsigned j = 0; j < edges_array.size() - 1; j++)
		{
			if (edges_array[j].weight > edges_array[j + 1].weight)
				swapStructs(edges_array[j], edges_array[j + 1]);
		}
	}
}

void swapStructs(Edges& first, Edges& second)
{
	char temp[sizeof(Edges)];
	std::memcpy(temp, &first, sizeof(Edges));
	std::memcpy(&first, &second, sizeof(Edges));
	std::memcpy(&second, temp, sizeof(Edges));
}

unsigned findIndexByVertId(const std::vector<Vertices>& vertices_array, unsigned id)
{
	unsigned index = 0;
	for (unsigned i = 0; i < vertices_array.size(); i++)
	{
		if (vertices_array[i].id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void makeMST(std::vector<Vertices>& vertices_array, std::vector<Edges>& edges_array)
{
	unsigned arr_size = edges_array.size();
	for (unsigned i = 0; i < arr_size; i++)
	{
		unsigned vert1_index = findIndexByVertId(vertices_array, edges_array[0].id_vertex1);
		unsigned vert2_index = findIndexByVertId(vertices_array, edges_array[0].id_vertex2);
		unsigned color1 = vertices_array[vert1_index].color;
		unsigned color2 = vertices_array[vert2_index].color;

		if (color1 != color2)
		{
			edges_array.push_back(edges_array[0]);
			setColor(vertices_array, color1, color2);
		}
		edges_array.erase(edges_array.begin());
	}
}

void setColor(std::vector<Vertices>& vertices_array, unsigned color1, unsigned color2)
{
	for (unsigned i = 0; i < vertices_array.size(); i++)
	{
		if (vertices_array[i].color == color2)
			vertices_array[i].color = color1;
	}
}

void printData(const std::vector<Vertices>& vertices_array, const std::vector<Edges>& edges_array)
{
	for (unsigned i = 0; i < edges_array.size(); i++)
	{
		unsigned vert1_index = findIndexByVertId(vertices_array, edges_array[i].id_vertex1);
		unsigned vert2_index = findIndexByVertId(vertices_array, edges_array[i].id_vertex2);

		cout << vertices_array[vert1_index].name << " ";
		cout << vertices_array[vert2_index].name << " ";
		cout << edges_array[i].weight << endl;
	}
}
