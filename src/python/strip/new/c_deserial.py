import struct 
import re
 
TYPES_DICT={"uint64_t":"Q","uint32_t":"I","uint16_t":"H","uint8_t":"B",
                 "int64_t":"q","int32_t":"i","int16_t":"h","int8_t":"b",
                 "char":"c","bool":"?","float":"f","double":"d",
                 "long long int":"q","unsigned long long int":"Q"};
 
class TupleReader():
    def __init__(self, data):
        self.index = 0
        self.data = data
    
    def read(self, length):
        if(length == 1):
            data = self.data[self.index]
        else:
            data = self.data[self.index:self.index+length]
        self.index += length
        return data
    

class Deserial():
    
    def __init__(self, c_struct, alignment="="):
        self.alignment = alignment
        self.varlist, self.pack_format = self.structInfo(c_struct)
        
    def structInfo(self, cStruct):
        TYPE_REGEX=re.compile("\\s*([a-zA-Z0-9_ ]+)\\s+(\\w+)(?:\\[(\\d*)\\])?;")
        pack_format=self.alignment
        varlist=[];
        for line in cStruct.splitlines():
            try:
                vartype, varname, arrayLength=TYPE_REGEX.findall(line)[0]
                vartype=TYPES_DICT[vartype];
                if arrayLength:
                    arrayLength=int(arrayLength);
                else:
                    arrayLength=1;
     
                pack_format+=vartype*arrayLength
                varlist.append([varname,arrayLength])
            except IndexError:
                pass
        return varlist, pack_format

    def size(self):
        return struct.calcsize(self.pack_format)

    def serial(self, fields):
        return struct.pack(self.pack_format, *fields )
        
    def to_dict(self, bindata):
        pack_format = self.pack_format
        
        unpacked=struct.unpack(pack_format, bindata )
        
        
        result = {}
        reader = TupleReader(unpacked)
        
        for name, length in self.varlist:
            result[name] = reader.read(length)

        return result
     
    
 
if __name__ == '__main__':
    MY_STRUCT="""typedef struct __attribute__ ((__packed__)){
    uint8_t u8;
    uint16_t u16;
    uint32_t u32;
    uint64_t u64;
    int8_t i8;
    int16_t i16;
    int32_t i32;
    int64_t i64;
    long long int lli;
    float flt;
    double dbl;
    char string[12];
    uint64_t array[5];
} debugInfo;"""
    
    PACKED_STRUCT=b'\x01\x00\x01\x00\x00\x01\x00\x00\x00\x00\x00\x01\x00\x00\x00\xff\x00\xff\x00\x00\xff\xff\x00\x00\x00\x00\xff\xff\xff\xff*\x00\x00\x00\x00\x00\x00\x00ff\x06@\x14\xaeG\xe1z\x14\x08@testString\x00\x00\x01\x00\x00\x00\x00\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00\x00\x00\x04\x00\x00\x00\x00\x00\x00\x00\x05\x00\x00\x00\x00\x00\x00\x00'
 
    
    d = Deserial(MY_STRUCT)
    
    print(d.to_dict(PACKED_STRUCT) )
    

