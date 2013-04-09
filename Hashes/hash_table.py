#!/usr/bin/env python

"""hash-table implementation"""

# import sdmb hashing function
import sdmb

class KeyNotFound(Exception):
    """key not found in hash_table"""

    def __init__(self, value):
        """ctor"""
        super(KeyNotFound, self).__init__(value)
        self.value = value
    
    def __str__(self):
        """error str"""
        return ''.join(["key not found: ", self.value])

    
class KeyValue:
    """class to represent each entry in hash table"""

    def __init__(self, key, value):
        """ctor for KeyValue"""
        self.key = key
        self.value = value

class HashTable:
    """class to represent the hash table"""

    # size of HashTable
    TABLESIZE = 10

    def __init__(self):
        """ctor for HashTable"""
        
        # empty list
        self.hash_table = list()

        # add TABLESIZE * buckets (lists)
        for _ in range(self.TABLESIZE):
            self.hash_table.append(list())


    def get_index(self, value):
        """get index for value: hash it and then apply modulo"""
        return sdmb.sdbm(value) % self.TABLESIZE

    def get_value(self, key):
        """get value for key"""
        
        #get index of key
        idx = self.get_index(key)

        if not len(self.hash_table[idx]):
            raise KeyNotFound(key)

        # search if key is found at this index
        for entry in self.hash_table[idx]:
            if entry.key == key:
                return entry.value
        raise KeyNotFound(key)

    def set_keyvalue(self, key, value):
        """add (key,value) in hash table"""
        
        # obtain index from key
        idx = self.get_index(key)

        
        # insert KeyValue at idx position, dealing with collisions

        # see if this bucket already contains the key
        for entry in self.hash_table[idx]:
            if entry.key == key:
                print "Already exists this key: {0}. No insertion will be done!".format(key)
                return

        # add KeyValue in bucket
        self.hash_table[idx].append(KeyValue(key, value))

    def show_hashtable(self):
        """prints the table"""
        print "----------------------------"
        for idx in range(self.TABLESIZE):

            if not len(self.hash_table[idx]):
                continue

            print "{0} ---> {1}".format(idx, [(item.key, item.value) for item in self.hash_table[idx]])
        
        print "----------------------------"


def show_value(htable, key):
    """gets value associated with this key"""
    try:
        value = htable.get_value(key)
        print "{0} -> {1}".format(key, value)
    except KeyNotFound as err:
        print "Warning: {0}".format(str(err))



def test_hash():
    """operations on hash table"""

    #create hash table
    htable = HashTable()

    # insert in hash table (duplicates will be discarded)
    htable.set_keyvalue("Judge", "321321")
    htable.set_keyvalue("Holden", "f32edqwd")
    htable.set_keyvalue("Glanton", "dasfsdnlfi")
    htable.set_keyvalue("Gomez", "323")
    htable.set_keyvalue("Kid", "32")
    htable.set_keyvalue("Tobin", "4dasd")
    htable.set_keyvalue("Bathcat", "132131")
    htable.set_keyvalue("Toadvine", "dscscs")
    htable.set_keyvalue("Kid", "newvale32")
    htable.set_keyvalue("Tobin", "newval4dasd")
    htable.set_keyvalue("Bathcat", "newval132131")
    htable.set_keyvalue("Toadvine", "newvaldscscs")

    # print hashtable
    htable.show_hashtable()

    # search the values associated with some keys
    keys = ["Judge", 'aaa', "Holden", "Tobin", "Toadvine", "Gomez"]
    for ckey in keys:
        show_value(htable, ckey)

if __name__ == '__main__':
    test_hash()
