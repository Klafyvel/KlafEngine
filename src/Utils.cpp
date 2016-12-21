#include <KlafEngine/Utils.hpp>

namespace klf
{
float intersect(float begin1, float end1, float begin2, float end2)
{
	if(begin1 > end1)
		intersect(end1, begin1, begin2, end2);
	else if(begin2 > end2)
		intersect(begin1, end1, end2, begin2);
	else if(begin1 > begin2)
		return intersect(begin2, end2, begin1, end1);
	else if(begin2 > end1)
		return -1;
	else if(end2 <= end1)
		return end2 - begin2;
	else 
		return end1 - begin2;
}
}
