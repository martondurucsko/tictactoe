#ifndef STATICTEXT_HPP
#define STATICTEXT_HPP

#include "widgets.hpp"

class StaticText : public Widget
{
public:
    StaticText(int,int,int,int,std::string);

protected:
    std::string _text;

    virtual void draw() override;
    virtual void handle(genv::event ev);
};

#endif // STATICTEXT_HPP
