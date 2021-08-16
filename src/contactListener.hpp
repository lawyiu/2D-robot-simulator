#ifndef CONTACT_LISTENER_HPP
#define CONTACT_LISTENER_HPP

#include <box2d/b2_world_callbacks.h>

class b2Contact;

class ContactListener : public b2ContactListener {
public:
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

private:
    void UpdateContact(b2Body* bodyA, b2Body* bodyB, bool overlap);
};

#endif /* CONTACT_LISTENER_HPP */
