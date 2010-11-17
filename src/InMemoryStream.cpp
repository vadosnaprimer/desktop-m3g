#include "m3g/InMemoryStream.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
using namespace std;


InMemoryStream:: InMemoryStream (const char* name) : cur(0)
{
    assert (name != 0);

    ifstream ifs (name);
    assert (ifs != 0);

    ifs.seekg (0, ios::end);
    int file_size = ifs.tellg ();
    ifs.seekg (0, ios::beg);

    buf.resize (file_size, 0);
    ifs.read (&buf[0], file_size);
}

InMemoryStream:: InMemoryStream (const char* p, int size) : cur(0)
{
    buf.assign (p, p+size);
}

InMemoryStream:: ~InMemoryStream ()
{
}

void InMemoryStream:: read (char* p, int size)
{
    assert (p != 0);

    memcpy (p, &buf[cur], size);
    cur += size;
}

void InMemoryStream:: seekg (int pos)
{
    assert (pos >= 0 && pos <= (int)buf.size());

    cur = pos;
}

unsigned int InMemoryStream:: tellg () const
{
    return cur;
}

bool InMemoryStream:: eof () const
{
    if (cur >= (int)buf.size())
        return true;
    else
        return false;
}

const char* InMemoryStream:: pointer () const
{
    return &buf[0];
}


int InMemoryStream:: size () const
{
    return buf.size();
}


void InMemoryStream:: erase (int pos, int size)
{
    assert (pos >= 0 && pos < (int)buf.size());
    assert (size >= 0 && size <= (int)buf.size());
    assert (pos+size <= (int)buf.size());

    buf.erase (buf.begin()+pos, buf.begin()+pos+size);
}

void InMemoryStream:: insert (int pos, const char* p, int size)
{
    assert (pos >= 0 && pos <= (int)buf.size());
    assert (p != 0);
    assert (size > 0);

    buf.insert (buf.begin()+pos, p, p+size);
}

