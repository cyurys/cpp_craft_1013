#include <string>
#include <iostream>
#include <fstream>
#include <map>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>

#include <reader.h>

using namespace binary_reader;

class Buffer
{
    static const boost::uint32_t BUFFER_SIZE = 2048u;
    std::map<boost::uint32_t, boost::uint32_t> cur_buf;
    std::map<boost::uint32_t, boost::uint32_t> total_msg;
    std::map<boost::uint32_t, boost::uint32_t> total_sec;
    boost::uint32_t cur_sec;
    void next_sec(boost::uint32_t sec);

public:
    void clear();
    Buffer& operator <<(Message const& msg);
    std::map<boost::uint32_t, double> get_average() ;//const;
};

void Buffer::next_sec(boost::uint32_t sec)
{
    cur_sec = sec;
    cur_buf.clear();
}

void Buffer::clear()
{
    cur_sec = 0;
    cur_buf.clear();
    total_msg.clear();
    total_sec.clear();
}

Buffer& Buffer::operator <<(Message const& msg)
{
    if (msg.get_time() > cur_sec)
        next_sec(msg.get_time());
    boost::uint32_t type = msg.get_type();
    if (cur_buf.count(type)==0u)
        ++total_sec[type];
    if (cur_buf[type]<BUFFER_SIZE)
    {
        ++cur_buf[type];
        ++total_msg[type];
    }
    return (*this);
}

std::map<boost::uint32_t, double> Buffer::get_average() //const
{
    std::map<boost::uint32_t, double> result;
    for( std::map<boost::uint32_t, boost::uint32_t>::iterator it = total_sec.begin(); it!=total_sec.end(); ++it)
        result[it->first] = ((double)total_msg[it->first])/((double)it->second);
    return result;
}

int main()
{
    //show_Message_binary_file_contents(BINARY_DIR "/2.5_example.in");
    //std::cout << std::endl;
    Buffer buf;
    buf.clear();
    {
        boost::shared_ptr<std::ifstream> input_file(new std::ifstream(BINARY_DIR "/input.txt", std::ifstream::binary));
        if(!input_file->is_open()) {std::cerr << "No input file(" << std::endl;return 1;}
        Message msg;

        while(*input_file >> msg) // while stream is good
            buf << msg;
    }
    std::map<boost::uint32_t, double> average = buf.get_average();
    boost::shared_ptr<std::ofstream> output_file(new std::ofstream(BINARY_DIR "/output.txt", std::ofstream::binary));
    for( std::map<boost::uint32_t, double>::iterator it = average.begin(); it!=average.end(); ++it)
    {
        output_file->write((char*)&(it->first), sizeof(boost::uint32_t));
        output_file->write((char*)&(it->second), sizeof(double));
        //std::cout << it->first << ' ' << it->second << std::endl;
    }
}

