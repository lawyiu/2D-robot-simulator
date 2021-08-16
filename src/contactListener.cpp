#include "contactListener.hpp"

#include <box2d/box2d.h>
#include "tape.hpp"
#include "lineSensor.hpp"

void ContactListener::UpdateContact(b2Body* bodyA, b2Body* bodyB, bool overlap) {
    Contactable* contactableA = reinterpret_cast<Contactable*>(bodyA->GetUserData().pointer);
    Contactable* contactableB = reinterpret_cast<Contactable*>(bodyB->GetUserData().pointer);

    if (contactableA && contactableB) {
        if (overlap) {
            contactableA->contactBegin(*contactableB);
            contactableB->contactBegin(*contactableA);
        } else {
            contactableA->contactEnd(*contactableB);
            contactableB->contactEnd(*contactableA);
        }
    }
}

void ContactListener::BeginContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    UpdateContact(bodyA, bodyB, true);
}

void ContactListener::EndContact(b2Contact* contact) {
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
    UpdateContact(bodyA, bodyB, false);
}
