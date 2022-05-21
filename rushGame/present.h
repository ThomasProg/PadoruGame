#ifndef _PRESENT_H_
#define _PRESENT_H_

#include "projectile.h"

class Present : public Projectile
{
private:

public:
	Present()
	{
		scoreAdded = 1800;
	}
};

#endif _PRESENT_H_