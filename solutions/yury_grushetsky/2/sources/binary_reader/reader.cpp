#include "reader.h"

//using namespace binary_reader;

binary_reader::Message::Message(uint32_t type, uint32_t time, uint32_t len, std::string msg)
	:TYPE(type), TIME(time), LEN(len), MSG(msg)	{}

binary_reader::Message::~Message() {}

boost::uint32_t binary_reader::Message::get_time() const { return TIME;}
		
std::istream & binary_reader::operator>>(std::istream& is, Message& msg)
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

std::ostream & binary_reader::operator<<(std::ostream& os, Message const & msg)
{
	os.write((const char*)&(msg.TYPE), sizeof(boost::uint32_t));
	os.write((const char*)&(msg.TIME), sizeof(boost::uint32_t));
	os.write((const char*)&(msg.LEN), sizeof(boost::uint32_t));
	const char* tmp = msg.MSG.c_str();
	os.write((const char*)&(tmp), (msg.LEN)*sizeof(char));
	return os;
}

void binary_reader::proxy_function_that_was_created_only_for_compiling_goals()
{
}

