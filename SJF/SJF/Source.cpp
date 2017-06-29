#include <iostream>
#include <vector>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <boost/geometry/algorithms/covered_by.hpp>

BOOST_GEOMETRY_REGISTER_BOOST_TUPLE_CS(cs::cartesian);

namespace SJF
{
	typedef unsigned short ushort;

	using boost::geometry::append;

	typedef boost::geometry::model::d2::point_xy<long> point;
	typedef boost::geometry::model::polygon<point> polygon;

	class SJF
	{
		ushort nrOfLargeSkyLanterns;
		ushort nrOfSmallSkyLanterns;
		polygon largeSkyLanterns;
		std::vector<point> smallSkyLanterns;

	public:
		SJF() = default;
		~SJF() = default;
		void loadData();
		polygon createConvexHull() const;
		ushort countNrOfPointsInPolygon(const polygon&) const;
	};
}

int main()
{
	SJF::SJF festival;
	festival.loadData();
	SJF::polygon convexHull = festival.createConvexHull();
	SJF::ushort nrOfSmallInterorBigBound = festival.countNrOfPointsInPolygon(convexHull);

	std::cout << nrOfSmallInterorBigBound << std::endl;

	return 0;
}

namespace SJF
{
	void SJF::loadData()
	{
		std::cin >> nrOfLargeSkyLanterns;
		long x, y;

		for (ushort i = 0; i < nrOfLargeSkyLanterns; i++)
		{
			std::cin >> x >> y;
			append(largeSkyLanterns, point(x, y));
		}

		std::cin >> nrOfSmallSkyLanterns;
		for (ushort i = 0; i < nrOfSmallSkyLanterns; i++)
		{
			std::cin >> x >> y;
			smallSkyLanterns.push_back(point(x, y));
		}
	}

	polygon SJF::createConvexHull() const
	{
		polygon convexHull;
		boost::geometry::convex_hull(largeSkyLanterns, convexHull);

		return convexHull;
	}

	ushort SJF::countNrOfPointsInPolygon(const polygon& convexHull) const
	{
		ushort nrOfPointsInPolygon = 0;

		for (ushort i = 0; i < nrOfSmallSkyLanterns; i++)
		{
			if (boost::geometry::covered_by(smallSkyLanterns[i], convexHull))
				nrOfPointsInPolygon++;
		}
		return nrOfPointsInPolygon;
	}
}
