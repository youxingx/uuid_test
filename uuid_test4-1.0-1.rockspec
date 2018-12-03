package = "uuid_test4"
version = "1.0-1"
source = {
    url = "git://github.com/youxingx/uuid_test.git",
    branch = "master"
}
description = {
    summary = "A test lua package with uuid",
    homepage = "https://github.com/youxingx/uuid_test",
    maintainer = "1097900172@qq.com",
    license = "MIT"
}
dependencies = {
    "lua >= 5.1, < 5.4"
}
build = {
    type = "make",
    install_variables = {
        INST_PREFIX="$(PREFIX)",
        INST_BINDIR="$(BINDIR)",
        INST_LIBDIR="$(LIBDIR)",
        INST_LUADIR="$(LUADIR)",
        INST_CONFDIR="$(CONFDIR)",
    },
}
