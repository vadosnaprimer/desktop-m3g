
#ifndef __OUT_MEMORY_STREAM__
#define __OUT_MEMORY_STREAM__


#include <vector>

/**
 * @~Japanese  出力専用メモリストリームクラス. 
 */
class OutMemoryStream
{
public:
    /**
     * @~Japanese  最終出力はファイルに書き出される.
     */
    OutMemoryStream (const char* file_name);
    ~OutMemoryStream ();

    void write (const char* p, int size);
    void seekp (int offset);

    int size () const;
    unsigned int tellp () const;

    void erase (int pos, int size);
    void insert (int pos, const char* p, int size);

    const char* pointer () const;

private:
    std::vector<char> buf;
    int               cur;
    const char*       name;
};


#endif


