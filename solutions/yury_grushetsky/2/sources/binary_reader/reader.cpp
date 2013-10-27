#include "reader.h"
#include <iostream>
#include <boost/shared_ptr.hpp>

namespace binary_reader
{
Message::Message(uint32_t type, uint32_t time, uint32_t len, std::string msg)
    :TYPE(type), TIME(time), LEN(len), MSG(msg)	{}

Message::~Message() {}//{std::cout << "Gone!!" << std::endl;}

boost::uint32_t Message::get_time() const { return TIME;}
boost::uint32_t Message::get_type() const { return TYPE;}

void Message::show()
{
    std::cout << TYPE << ' ' << TIME << ' ' << LEN << ' ' << MSG << std::endl;
}

std::ifstream& operator>>(std::ifstream& is, Message& msg)
{
    is.read((char*)&(msg.TYPE), sizeof(boost::uint32_t));
    is.read((char*)&(msg.TIME), sizeof(boost::uint32_t));
    is.read((char*)&(msg.LEN), sizeof(boost::uint32_t));
    char* buf = new char[msg.LEN]; //TODO ?? make const buffer of MAX_SIZE or use char* for field MSG
    is.read((char*)buf, (msg.LEN)*sizeof(char));
    msg.MSG.assign(buf, msg.LEN);
    delete[] buf;
    return is;
}

std::ofstream& operator<<(std::ofstream& os, Message const & msg)
{
    os.write((const char*)&(msg.TYPE), sizeof(boost::uint32_t));
    os.write((const char*)&(msg.TIME), sizeof(boost::uint32_t));
    os.write((const char*)&(msg.LEN), sizeof(boost::uint32_t));
    //const char* tmp = msg.MSG.c_str();
    //os.write((const char*)&(tmp), (msg.LEN)*sizeof(char));
    os.write(msg.MSG.c_str(), (msg.LEN)*sizeof(char));
    return os;
}

void show_Message_binary_file_contents(const char* filename)
{
    boost::shared_ptr<std::ifstream> inp_file(new std::ifstream(filename, std::ifstream::binary));
    boost::shared_ptr<Message> cur(new Message());
    while(inp_file->is_open() && !inp_file->eof())
    {
        *inp_file >> *cur;
        if(*inp_file)
            cur->show();
    }
}

void proxy_function_that_was_created_only_for_compiling_goals()
{
}
}
