#include "m3g/OutMemoryStream.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstring>
using namespace std;


OutMemoryStream:: OutMemoryStream (const char* name_) : cur(0), name(name_)
{
    assert (name != 0);
}

OutMemoryStream:: ~OutMemoryStream ()
{
    if ((int)buf.size() > 0) {
        ofstream ofs (name);
        assert (ofs != 0);
        ofs.write (&buf[0], buf.size());
    }
}

void OutMemoryStream:: write (const char* p, int size)
{
    assert (p != 0);
    assert (size > 0);

    if (cur + size > (int)buf.size()) {
        buf.resize (cur + size, 0);
    }

    copy (p, p+size, buf.begin()+cur);
    cur += size;
}

unsigned int OutMemoryStream:: tellp () const
{
    return cur;
}

void OutMemoryStream:: seekp (int pos)
{
    assert (pos >= 0 && pos <= (int)buf.size());

    cur = pos;
}

int OutMemoryStream:: size () const
{
    return buf.size();
}

void OutMemoryStream:: erase (int pos, int size)
{
    assert (pos >= 0 && pos < (int)buf.size());
    assert (size >= 0 && size <= (int)buf.size());
    assert (pos+size <= (int)buf.size());

    buf.erase (buf.begin()+pos, buf.begin()+pos+size);
}

void OutMemoryStream:: insert (int pos, const char* p, int size)
{
    assert (pos >= 0 && pos <= (int)buf.size());
    assert (p != 0);
    assert (size > 0);

    buf.insert (buf.begin()+pos, p, p+size);
}


const char* OutMemoryStream:: pointer () const
{
    return &buf[0];
}

