#include <iostream>
#include <string>
#include <vector>
#include <codecvt>
#include <fstream>

/**
 * \brief Namespace for Karpin Rabin algrithm.
 */
namespace KR
{
	/**
	 * \brief Set 'ulong' as an alias of 'unsigned long'.
	 */
	typedef unsigned long ulong;

	class KarpinRabin
	{
		std::wstring textFromFile; /*!< An array with string loaded from file.*/
		std::wstring pattern; /*!< An array with pattern string.*/
		std::vector<ulong> indexesOfEqualHashes; /*!< An array with indexes, where hashes from text equals pattern's hash. */

		/**
		 * \brief A function to load file with text. 
		 * \param filename string.
		 */
		void loadFile(const std::string& filename);
		/**
		 * \brief A function to create hash by adding all of the chararcters separately.
		 * \param source - source to create hash one by one on it.
		 * \return usigned long value, a hash.
		 */
		ulong createHashOneByOne(std::wstring& source) const;
		/**
		 * \brief A function to create hash based on previous hash (rolling hash). 
		 * It's overwritting hash (previous hash) value.
		 * \param hash Previous hash value.
		 * \param first An index of letter that has to be deleted.
		 * \param last An index of letter that has to be added.
		 */
		void createHashFromPrevious(ulong& hash, ulong first, ulong last);

	public:
		/**
		 * \brief Default constructor.
		 */
		KarpinRabin() = default;
		/**
		 * \brief Default destructor.
		 */
		~KarpinRabin() = default;
		/**
		 * \brief A function to load data from standard input. 
		 */
		void loadData();
		/**
		 * \brief A function that creates an array of indexes, where the hashes equals pattern hash.
		 */
		void createArrayOfPropHash();
		/**
		 * \brief Compare if the string equals pattern. If no, then delete this index from ArrayOfPropHash.
		 */
		void compareStrings();
		/**
		 * \brief Show indexes of found strings that equals pattern.
		 */
		void showIdsOfFoundStrings();
	};
}

int main()
{
	KR::ulong nrOfTestCases = 0;
	std::cin >> nrOfTestCases;
	for (KR::ulong i = 0; i < nrOfTestCases; i++)
	{
		KR::KarpinRabin* karpinRabin = new KR::KarpinRabin();
		karpinRabin->loadData();
		karpinRabin->createArrayOfPropHash();
		karpinRabin->compareStrings();
		karpinRabin->showIdsOfFoundStrings();
		delete karpinRabin;
	}

	return 0;
}

namespace KR
{
	void KarpinRabin::loadFile(const std::string& filename)
	{
		std::wifstream in(filename, std::wifstream::in);
		//in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>)); //handle utf8
		if (in.is_open())
		{
			while (!in.eof())
				textFromFile.push_back(in.get());
		}
		in.close();

		while (std::wcin.get() != '\n'); //skip enter
	}

	void KarpinRabin::loadData()
	{
		std::string filename;
		std::cin >> filename;
		loadFile(filename);
		//std::wcin.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>)); //handle utf8
		std::getline(std::wcin, pattern);
	}


	ulong KarpinRabin::createHashOneByOne(std::wstring& source) const
	{
		int base = 2;
		ulong maxPowExponent = pattern.size() - 1;
		ulong hash = 0;
		for (ulong i = 0; i < pattern.size(); i++)
		{
			ulong baseMultiplied = ulong(pow(base, maxPowExponent--));
			hash += ulong(ulong(source[i]) * baseMultiplied);
		}
		return hash;
	}

	void KarpinRabin::createHashFromPrevious(ulong& hash, ulong first, ulong last)
	{
		int base = 2;
		ulong maxPowExponent = pattern.size() - 1;

		ulong baseMultiplied = ulong(pow(base, maxPowExponent));
		ulong oddValue = ulong(ulong(textFromFile[first]) * baseMultiplied);

		hash -= oddValue;
		hash *= base;
		hash += ulong(textFromFile[last]);
	}

	void KarpinRabin::createArrayOfPropHash()
	{
		ulong patternHash = createHashOneByOne(pattern);
		ulong hash = createHashOneByOne(textFromFile);

		if (hash == patternHash)
			indexesOfEqualHashes.push_back(0);

		for (ulong i = 0, position = 1; i < textFromFile.size() - pattern.size(); i++)
		{
			createHashFromPrevious(hash, i, i + pattern.size());

			if (hash == patternHash)
				indexesOfEqualHashes.push_back(position);

			position++;
		}
	}

	void KarpinRabin::compareStrings()
	{
		ulong sizeOfHashesArray = indexesOfEqualHashes.size();
		for (ulong i = 0, id = 0; i < sizeOfHashesArray; i++)
		{
			if (textFromFile.compare(indexesOfEqualHashes[id], pattern.size(), pattern) != 0)
			{
				indexesOfEqualHashes.erase(indexesOfEqualHashes.begin() + id);
				continue;
			}
			id++;
		}
	}

	void KarpinRabin::showIdsOfFoundStrings()
	{
		for (ulong x : indexesOfEqualHashes)
			std::cout << x << " ";
		std::cout << std::endl;
	}
}
