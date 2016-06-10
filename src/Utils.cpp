#include <KlafEngine/Utils.hpp>

float intersect(float begin1, float end1, float begin2, float end2)
{
	assert(begin1 <= end1);
	assert(begin2 <= end2);

	if(begin1 > begin2)
		return intersect(begin2, end2, begin1, end1);
	else if(begin2 >= end1)
		return 0;
	else if(end2 <= end1)
		return end2 - begin2;
	else
		return end1 - begin2;
}

