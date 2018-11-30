package = "uuid_test"
version = "uuid-1"
source = {
    url = "git@github.com:youxingx/uuid_test.git"
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
    type = "builtin",
    modules = {
        uuid_test = "clib/uuid.c",
        ["uuid_test"] = "resty/uuid.lua"
    }
}
