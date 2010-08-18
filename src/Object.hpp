#ifndef __OBJECT_HPP__
#define __OBJECT_HPP__

#include <iosfwd>

namespace m3g {


    /**
     * @~English   The basis of all classes.
     * @~Japanese  全てのオブジェクトの規程となるクラス.
     */
    class Object
    {

    public:

        /**
         * @~English   Constructs an Object object with default values.
         * @~Japanese  このObjectオブジェクトを作成するコンストラクタ.
         */
        Object ();

        /**
         * @~English  Destruct this object.
         * @~Japanese このオブジェクトを破壊するデストラクタ.
         */
        ~Object ();

        /**
         * @~Enslish   get mark of this object referenced by external library.
         * @~Japanese  外部ライブラリからこのオブジェクトを参照するのに必要なデータを取得する.
         */
        void* getExportedEntity () const;

        /**
         * @~Enslish   set mark of this object referenced by external library.
         * @~Japanese  外部ライブラリからこのオブジェクトを参照するのに必要なデータをセットする.
         */
        void setExportedEntity (void* entity);

        /**
         * @~Enslish   mark this for Garbage Collect.
         * @~Japanese  GCコレクター用のマークを行う.
         */
        virtual void mark (void(*func)(void*)) const;

        /**
         * @~English  Print out information of this class, for debug only.
         * @~Japanese このObjectクラスの情報を表示する。デバッグ用.
         */
        std::ostream& print (std::ostream& out) const;

    private:

        void* exported_entity;
    };

}  // using namespace std;

std::ostream& operator<< (std::ostream& out, const m3g::Object& obj);


#endif
