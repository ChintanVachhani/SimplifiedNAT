# SimplifiedNAT
A simplified version of Network Address Translation (NAT).


### General Information
* Run the project from 'main.cpp' using the provided cmake file.
* Remember to make sure the project working directory is the repository's folder.
* __Address__ class is used to represent the network address.
* __NAT__ class handles the implementation for the solution. It uses a map based data structure to represent the network address mappings. It provides methods to - 
  * map a network address to another
  * translate a network address to its corresponding mapping
  * load all the mapping from an input file
  * read each input network address, translate to its mapped address and write the output to a file.
* __Utility__ class to provide string utility methods such as a method to split string into a vector of strings, trim a string, etc.


### Other Considerations & Further Optimizations
Right now the __Address__ class has an object of size ~16 bytes. Further, this would mean that the __NAT__ class object would be approximately of size [12 + [4 * P (# of Ports mapped for an IP)]] * N (# of unique IPs mapped) bytes. I feel this can be improved by representing an IP address as integer array of size 4 and port number as an integer. This would make the __Address__ object to be of 10 bytes and reducing the size of __NAT__ object even more.
Also, using integer gives a scope to implement a solution to search for IP in O(log n) complexity using sorting and binary search type of logic. This might be better considering that a map based solution might have a worst case complexity of O(n) on rare occasions though most of the time it is a constant time solution. But map less solution definitely gives a window to reduce the space complexity even further.
Another thing to consider would be scaling. Storing the mappings on memory would not be the best idea always and in case of large scale data, this can be transformed to run on partitioned data files in parallel.

