#ifndef CONTACTABLE_HPP
#define CONTACTABLE_HPP

class Contactable {
public:
    virtual void contactBegin(Contactable& other) = 0;
    virtual void contactEnd(Contactable& other) = 0;

protected:
    ~Contactable() {};
};

#endif /* CONTACTABLE_HPP */
