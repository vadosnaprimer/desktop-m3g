

# =========================
# NDK 2.3 
# Android-NDKのSTLおよび例外、
# 実行情報のサポートは完全ではなく
# 組合せによってはエラーが出る。
# ========================

#APP_STL := stlport_static
# (Error) undefined reference to `typeinfo for std::ios_base'

#APP_STL := stlport_shared
# (Error) undefined reference to `typeinfo for std::ios_base'

APP_STL := gnustl_static
# (OK)

#APP_STL := gnustl_shared
# 2.3ではまだ存在しない


#
# メモ：dynamicリンクの時は使用前に
# static {
#    System.loadLibrary("stlport_shared");
# }
#

