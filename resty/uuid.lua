
module("resty.uuid", package.seeall)

_VERSION = '0.01'

local ffi = require "ffi"
local ffi_new = ffi.new
local ffi_str = ffi.string

ffi.cdef[[
void uuid8(char *out);
void uuid20(char *out);
void uuid94hex(char *out);
void uuid64hex(char *out);
void uuid128hex(char* uuidRes);
void uuid256hex(char* uuidRes);
void uuid94hexbyuuid(char* uuidRes,char* uuid);
void uuid64hexbyuuid(char* uuidRes,char* uuid);
void uuid128hexbyuuid(char* uuidRes,char* uuid);
void uuid256hexbyuuid(char* uuidRes,char* uuid);
]]

local libuuid = ffi.load("libuuidx")

function gen8()
    if libuuid then
        local result = ffi_new("char[9]")
        libuuid.uuid8(result)
        return ffi_str(result)
    end
end

function gen20()
    if libuuid then
        local result = ffi_new("char[21]")
        libuuid.uuid20(result)
        return ffi_str(result)
    end
end


function gen94hex(_uuidstr)
    if not _uuidstr then
        if libuuid then
            local result = ffi_new("char[32]")
            libuuid.uuid94hex(result)
            return ffi_str(result)
        end
    else
        if libuuid then
            local result = ffi_new("char[32]")
            local srcuuid = ffi_new("char[40]",_uuidstr)
            libuuid.uuid94hexbyuuid(result,srcuuid)
            return ffi_str(result)
        end

    end
end


function gen64hex(_uuidstr)
    if not _uuidstr then
        if libuuid then
            local result = ffi_new("char[32]")

            libuuid.uuid64hex(result)
            return ffi_str(result)
        end
    else
        if libuuid then
            local result = ffi_new("char[32]")
            local srcuuid = ffi_new("char[40]",_uuidstr)
            libuuid.uuid64hexbyuuid(result,srcuuid)
            return ffi_str(result)
        end
    end

end

function gen128hex(_uuidstr)
    if not _uuidstr then
        if libuuid then
            local result = ffi_new("char[32]")

            libuuid.uuid128hex(result)
            return ffi_str(result)
        end
    else
        if libuuid then
            local result = ffi_new("char[32]")
            local srcuuid = ffi_new("char[40]",_uuidstr)
            libuuid.uuid128hexbyuuid(result,srcuuid)
            return ffi_str(result)
        end
    end

end


function gen256hex(_uuidstr)
    if not _uuidstr then
        if libuuid then
            local result = ffi_new("char[32]")

            libuuid.uuid256hex(result)
            return ffi_str(result)
        end
    else
        if libuuid then
            local result = ffi_new("char[32]")
            local srcuuid = ffi_new("char[40]",_uuidstr)
            libuuid.uuid256hexbyuuid(result,srcuuid)
            return ffi_str(result)
        end
    end

end

-- to prevent use of casual module global variables
getmetatable(resty.uuid).__newindex = function (table, key, val)
    error('attempt to write to undeclared variable "' .. key .. '": '
            .. debug.traceback())
end
