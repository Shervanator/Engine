//
//  Author: Shervin Aflatooni
//

#include "SphereCollider.h"

SphereCollider::SphereCollider(float size, float mass) : BaseCollider(new btSphereShape(size), mass)
{
}
