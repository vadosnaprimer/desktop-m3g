
---

## Important notice ##
In most cases, binary packages are sufficient for you.
If you need samples, Try svn checkout all sources from the repository.


---

## Brief description ##

Desktop-M3G is a C++ Implementation of M3G-1.1 (JSR-184) API for desktop use.

It works on Ubuntu and Android.

If you want to use from Java, Try Desktop-M3G + [Java-M3G](http://code.google.com/p/java-m3g/).

These images are captured on Android 2.2 / TOSHIBA Dynabook AZ.
It works well.

![http://desktop-m3g.googlecode.com/svn/trunk/doc/images/sc201103241438340.jpg](http://desktop-m3g.googlecode.com/svn/trunk/doc/images/sc201103241438340.jpg)


Related projects : [java-m3g project](http://code.google.com/p/java-m3g/) , [ruby-m3g project](http://code.google.com/p/ruby-m3g/) , [m3g-viewer](http://code.google.com/p/m3g-viewer/) , [m3g-exporter-for-metasequoia](http://code.google.com/p/m3g-exporter-for-metasequoia/), [m3g-reader-writer](http://code.google.com/p/m3g-reader-writer/)


---

## Latest Release ##

Latest version of 0.3.4  was released at 2011/12/16.

2011/12/16 ver 0.3.4
  * relax maxmum index number from ushort to int in OpenGL.
    * M3G-1.1 specification restricts vertices less than 65,535(=USHRT\_MAX).
    * But because it is not enough for desktop use,
    * Desktop-M3G relaxes this number to 2,147,483,647(=INT\_MAX).
  * change TriangleStripArray constructor API
    * you need to set number of indices explicitly
  * change Mesh constructor API
    * you need to set number of appearances explicitly
  * remove dependency for m3g-reader-writer
    * take all sources from the projects into Desktop-M3G
  * remove dependency for libpng, libjpeg
    * Instead of these library, Desktop-M3G uses Sean Barrett's image library
    * It is usefull especially for Android



---

## Main feature ##
  * It is implemented in C++ (not in Java)
  * It uses OpenGL (not OpenGL ES)
  * It can be used from Ruby (ruby-m3g) and Java (java-m3g)


---

## Current status ##
| 2011/12/16  | ver 0.3.4 | β release |
|:------------|:----------|:----------|
| 2011/05/17  | ver 0.3.3 | β release |
| 2010/12/1   | ver 0.3.2 | α5 release |
| 2010/08/8   | ver 0.3.1 | α4 release |
| 2010/6/6    | ver 0.3.0 | α3 release |
| 2010/5/10   | ver 0.2.0 | α2 release |
| 2010/4/8    | ver 0.1   | first α release |


---

## Requirement ##
  * Linux or Android
  * OpenGL 1.5 or above (Linux)
  * OpenGL ES 1.1 or above (Android)
  * libz
  * and other tools (g++, cmake, UnitTest++, ...)
