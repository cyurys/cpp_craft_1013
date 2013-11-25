#include "b_message.h"

#include <stdexcept>
#include <boost/lexical_cast.hpp>

task4_4::b_message::b_message( std::istream& inp )
{
	inp >> length_;
    if ( inp.eof() )
        throw std::logic_error("bad input stream, b_message cannot be readed");
    content_ = new char[ length_ ];
    inp.get(); //skip " "
	inp.read( content_, length_ );
    if ( inp.eof() )
    {
        throw std::logic_error("bad input stream, b_message cannot be readed");
        delete [] content_;
    }
}

task4_4::message_ptr task4_4::b_message::create_message( std::istream& inp )
{
	return message_ptr( new b_message( inp ) );
}

task4_4::b_message::~b_message()
{
	delete [] content_;
}

const char task4_4::b_message::type() const
{
	return 'B';
}
const std::string task4_4::b_message::str() const
{
    std::string msg = std::string("b_message(");
    msg += boost::lexical_cast<std::string>(length_);
    msg.push_back('|');
    for(size_t i = 0; i < length_; i++)
    {
        msg.push_back(content_[i]);
    }
    msg.push_back(')');
    return msg;
}
