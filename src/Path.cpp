/*
 * Path.cpp
 *
 *  Created on: Apr 29, 2016
 *      Author: thallock
 */

#include "Path.h"

#include <iomanip>

Path::Path() {}

Path::~Path() {}

std::ostream& Path::print(std::ostream& out) {

	auto e = path.end();
	for (auto i = path.begin(); i!=e; ++i)
		out << std::setw(4) << *i << ' ';

	out << '\n';
	return out;
}

double Path::getCost(Graph& g/*, bool forward*/) {
	double cost = 0;

	int prevNode = path.front();
	const auto e = path.end();
	for (auto i = ++path.begin(); i!=e; ++i)
	{
//		std::cout << "" << g.getNode(prevNode).getCostTo(*i, true) << std::endl;
		cost += g.getNode(prevNode).getCostTo(*i, true);
		prevNode = *i;
	}

//	std::cout << "Total cost is " << cost << std::endl;

	return cost;
}

Path& Path::operator =(const Path& other) {
	path = other.path;
	return *this;
}

bool Path::operator ==(const Path& other) const {
	if (path.size() != other.path.size())
		return false;

	auto e = path.end();
	auto i = path.begin();
	auto o = other.path.begin();
	while (i != e)
		if (*(i++) != *(o++))
			return false;

	return true;
}




void createOptimalPath(std::list<int>& vec)
{

	vec.push_back(31120);
	vec.push_back(31123);
	vec.push_back(31128);
	vec.push_back(31135);
	vec.push_back(31142);
	vec.push_back(31166);
	vec.push_back(31313);
	vec.push_back(31429);
	vec.push_back(31540);
	vec.push_back(31714);
	vec.push_back(31827);
	vec.push_back(32145);
	vec.push_back(32326);
	vec.push_back(32519);
	vec.push_back(32715);
	vec.push_back(32984);
	vec.push_back(33270);
	vec.push_back(33373);
	vec.push_back(33526);
	vec.push_back(33675);
	vec.push_back(33791);
	vec.push_back(33916);
	vec.push_back(34018);
	vec.push_back(34059);
	vec.push_back(34176);
	vec.push_back(34266);
	vec.push_back(34369);
	vec.push_back(34400);
	vec.push_back(34537);
	vec.push_back(34663);
	vec.push_back(34686);
	vec.push_back(34810);
	vec.push_back(34961);
	vec.push_back(35208);
	vec.push_back(35424);
	vec.push_back(35644);
	vec.push_back(35729);
	vec.push_back(35849);
	vec.push_back(36040);
	vec.push_back(36237);
	vec.push_back(36795);
	vec.push_back(36924);
	vec.push_back(37149);
	vec.push_back(37342);
	vec.push_back(37632);
	vec.push_back(37762);
	vec.push_back(37972);
	vec.push_back(37988);
	vec.push_back(38146);
	vec.push_back(38210);
	vec.push_back(38219);
	vec.push_back(38228);
	vec.push_back(38246);
	vec.push_back(38264);
	vec.push_back(38297);
	vec.push_back(38358);
	vec.push_back(38426);
	vec.push_back(38494);
	vec.push_back(38611);
	vec.push_back(38785);
	vec.push_back(38896);
	vec.push_back(39142);
	vec.push_back(39291);
	vec.push_back(39538);
	vec.push_back(39932);
	vec.push_back(40128);
	vec.push_back(40457);
	vec.push_back(40698);
	vec.push_back(41377);
	vec.push_back(41746);
	vec.push_back(42359);
	vec.push_back(42697);
	vec.push_back(43045);
	vec.push_back(43439);
	vec.push_back(44251);
	vec.push_back(44807);
	vec.push_back(45223);
	vec.push_back(45903);
	vec.push_back(46114);
	vec.push_back(46256);
	vec.push_back(46398);
	vec.push_back(46523);
	vec.push_back(46686);
	vec.push_back(46848);
	vec.push_back(47081);
	vec.push_back(47347);
	vec.push_back(47581);
	vec.push_back(47816);
	vec.push_back(48164);
	vec.push_back(48543);
	vec.push_back(48918);
	vec.push_back(49265);
	vec.push_back(49586);
	vec.push_back(49973);
	vec.push_back(49979);
	vec.push_back(50442);
	vec.push_back(50836);
	vec.push_back(51276);
	vec.push_back(51725);
	vec.push_back(52168);
	vec.push_back(52585);
	vec.push_back(53020);
	vec.push_back(53459);
	vec.push_back(53872);
	vec.push_back(54299);
	vec.push_back(54657);
	vec.push_back(54971);
	vec.push_back(55405);
	vec.push_back(55545);
	vec.push_back(55715);
	vec.push_back(56069);
	vec.push_back(56229);
	vec.push_back(56376);
	vec.push_back(56524);
	vec.push_back(56662);
	vec.push_back(56895);
	vec.push_back(57080);
	vec.push_back(57306);
	vec.push_back(57534);
	vec.push_back(57934);
	vec.push_back(58464);
	vec.push_back(59266);
	vec.push_back(59908);
	vec.push_back(59912);
	vec.push_back(59975);
	vec.push_back(59988);
	vec.push_back(60051);
	vec.push_back(60095);
	vec.push_back(60122);
	vec.push_back(60159);
	vec.push_back(60213);
	vec.push_back(60299);
	vec.push_back(60408);
	vec.push_back(60512);
	vec.push_back(60592);
	vec.push_back(61446);
	vec.push_back(61445);
	vec.push_back(61490);
	vec.push_back(61555);
	vec.push_back(61609);
	vec.push_back(61657);
	vec.push_back(61744);
	vec.push_back(62275);
	vec.push_back(62274);
	vec.push_back(62363);
	vec.push_back(62441);
	vec.push_back(62508);
	vec.push_back(62567);
	vec.push_back(62639);
	vec.push_back(62714);
	vec.push_back(62824);
	vec.push_back(62886);
	vec.push_back(62942);
	vec.push_back(62974);
	vec.push_back(62959);
	vec.push_back(62930);
	vec.push_back(62870);
	vec.push_back(62841);
	vec.push_back(62718);
	vec.push_back(62560);
	vec.push_back(62321);
	vec.push_back(62114);
	vec.push_back(61896);
	vec.push_back(61662);
	vec.push_back(61526);
	vec.push_back(61400);
	vec.push_back(60813);
	vec.push_back(60493);
	vec.push_back(60157);
	vec.push_back(59806);
	vec.push_back(59513);
	vec.push_back(59294);
	vec.push_back(59077);
	vec.push_back(58913);
	vec.push_back(58816);
	vec.push_back(58770);
	vec.push_back(58671);
	vec.push_back(58515);
	vec.push_back(58386);
	vec.push_back(58245);
	vec.push_back(58095);
	vec.push_back(57950);
	vec.push_back(57767);
	vec.push_back(57583);
	vec.push_back(57404);
	vec.push_back(57247);
	vec.push_back(57038);
	vec.push_back(56827);
	vec.push_back(56566);
	vec.push_back(56290);
	vec.push_back(56024);
	vec.push_back(55811);
	vec.push_back(55572);
	vec.push_back(55301);
	vec.push_back(55078);
	vec.push_back(54862);
	vec.push_back(54725);
	vec.push_back(54670);
	vec.push_back(54660);
	vec.push_back(54576);
	vec.push_back(54441);
	vec.push_back(54234);
	vec.push_back(53995);
	vec.push_back(53743);
	vec.push_back(53481);


	vec.reverse();
}
