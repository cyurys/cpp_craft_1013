#include <string>
#include <iostream>
#include <fstream>

#include <boost/cstdint.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/array.hpp>

#include <reader.h>

typedef boost::shared_ptr< std::string > string;
typedef boost::scoped_ptr< std::string > string_ptr;
typedef boost::array< int, 100 > int_array;

string f()
{
	return string( new std::string( "hello shared world" ) );
}

void f2( string_ptr& ptr )
{
	return ptr.reset( new std::string( "wow wow" ) );
}

int_array f3()
{
	int_array a;
	a[ 5 ] = 15;
	return a;
}

class inf
{
public:
	int a;
	inf(int n) :a(n){}
	void close() {std::cout << a++ << " Yyyeeeees!" << std::endl;}
	~inf() {close();}
};

int main()
{
	boost::shared_ptr< inf> p( new inf(5));
	p->close();
	std::ifstream input_file( BINARY_DIR "/2.4_example.in", std::ifstream::binary);
	char buf[100];
	if(input_file && !input_file.eof())
	{
		boost::uint32_t TYPE, TIME, LEN;
		input_file.read((char*)&TYPE, sizeof(boost::uint32_t));
		input_file.read((char*)&TIME, sizeof(boost::uint32_t));
		input_file.read((char*)&LEN, sizeof(boost::uint32_t));
		input_file.read((char*)buf, LEN*sizeof(char));
		std::cout << "TYPE=" << TYPE << std::endl;
		std::cout << "TIME=" << TIME << std::endl;
		std::cout << "LEN=" << LEN << std::endl;
		std::cout << "MSG=" << buf << std::endl;
	}
	//input_file.close();
	
	//std::ifstream input_file( BINARY_DIR "/2.4_example.in", std::ifstream::binary);
	if(input_file && !input_file.eof())
	{
		binary_reader::Message msg;
		input_file >> msg;
		std::cout << "TIME=" << msg.get_time() << std::endl;
	}
	input_file.close();

	{
		boost::shared_ptr<std::ofstream> ofs( new std::ofstream( BINARY_DIR "/out.txt"));
		*ofs << "hi" << std::endl;
	}
	{
		string s = f();
		string s2 = s;
		std::cout << s2->c_str() << std::endl;
	}
	{
		string_ptr ps;
		f2( ps );
		std::cout << ps->c_str() << std::endl;

		// string_ptr sp2 = ps; // uncomment to get in troubles
	}
	{
		int_array ia = f3();
		std::cout << ia[5] << std::endl;
	}
}

