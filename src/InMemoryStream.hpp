
#ifndef __IN_MEMORY_STREAM__
#define __IN_MEMORY_STREAM__

#include <vector>

/**
 * @~Japanese  読み込み専用メモリストリームクラス.
 */
class InMemoryStream
{
public:
    InMemoryStream (const char* file_name);
    InMemoryStream (const char* p, int size);
    ~InMemoryStream ();

    void read  (char* p, int size);
    void seekg (int pos);

    int size   () const;
    unsigned int tellg () const;
    bool eof () const;


    void erase  (int pos, int size);
    void insert (int pos, const char* buf, int size);

    const char* pointer () const;


private:
    std::vector<char> buf;
    int               cur;
};


#endif


