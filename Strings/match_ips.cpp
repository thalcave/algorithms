#include <set>
#include <map>
#include <string>
#include <iostream>
#include <stdexcept>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
/*
 * IspCountMap

- We have a log of a large DOS attack on our servers, including source IPs. We have a data file, with ISPs worldwide, their IP numbers and subnets (IPv4) 
(IP numbers/N, where N means all IPs with that many beginning bits it common with the IP given). Output the ISPs with the 10 largest number of attacking source IPs, and the counts of such IPs from their subnets.

example of log entry
1.2.3.4 \t other fields
lots of lines like this

the ISP data file: (~20 000 entries)
ISPa 1.2.3.5/29
ISPa 3.4.5.6/30
ISPb 3.3.5.9/31

 */


//class holding an IPv4: bl1.bl2.bl3.bl4
class Ipv4
{
public:
	Ipv4(std::string const& ip): ip_(ip)
	{
		boost::split(octets, ip, boost::is_any_of("."));
		if (octets.size() != 4)
		{
			throw std::logic_error("Invalid ip: " + ip);
		}
	}
	
	const std::string& getIp() const { return ip_; }
	std::string getOctet(unsigned n) const { return octets.at(n-1); }
	//get first n octets
	std::string getPartialIp(unsigned n) const 
	{
		if (n > octets.size() || !n)
		{
			throw std::logic_error("Invalid no. of octets");
		}

		std::string result = octets.at(0);
		for (unsigned i = 1; i < n; ++i)
		{
			result += "." + octets.at(i);
		}
		
		return result;
	}
private:
	std::string ip_;
	std::vector<std::string> octets;
};


//class holding a CIDR: ipv4/prefix
class Cidr
{
public:
	Cidr(std::string const& cidr): cidr_(cidr), ip_(init())
	{
		
	}
	
	Ipv4 init()
	{
		std::string::size_type pos = cidr_.find("/");
		if (pos == std::string::npos)
		{
			throw std::logic_error("Invalid cidr: "+cidr_);
		}
		
		prefix_.assign(cidr_, pos+1, cidr_.length());
		prefix_no = boost::lexical_cast<unsigned>(prefix_);
		
		return Ipv4(cidr_.substr(0, pos));
	}
	
	const std::string& getCidr() const { return cidr_; }
	const std::string& getPrefix() const { return prefix_; }
	const Ipv4& getIp() const { return ip_; }
	
	/* if prefix_no < 8 --> 0 blocks
			< 16 --> 1 blocks
			< 24 --> 2 blocks
			else --> 3 blocks
	*/
	unsigned getNoRelevantBlocks() const
	{
		return prefix_no/8;
	}
	
	std::string getRelevantBlocks() const
	{
		return ip_.getPartialIp(getNoRelevantBlocks());
	}
	
	/*match IP:
	 * 	check first X blocks to match
	 * 	check last blocks: bitwise
	*/
	bool matchesIp(std::string const& ip) const
	{
		std::cout<<"match :"<<ip<<" against: "<<cidr_<<"\n";
		Ipv4 test_ip(ip);
		unsigned no_blocks = getNoRelevantBlocks();
		if (ip_.getPartialIp(no_blocks) != test_ip.getPartialIp(no_blocks))
		{
			std::cout<<"ip_.getPartialIp(no_blocks) != ip.getPartialIp(no_blocks): "<<ip_.getPartialIp(no_blocks) << " != "<<test_ip.getPartialIp(no_blocks)<<std::endl;
			return false;
		}
		
		std::cout<<"first "<<no_blocks<<" matched\n";
		
		//get last block
		unsigned last_block(boost::lexical_cast<unsigned>(test_ip.getOctet(no_blocks + 1)));
		std::cout<<"last block from ip: "<<last_block<<"\n";

		
		unsigned remainder = 32 - prefix_no;
		
		//check first 'remainder' bits
		last_block >>=remainder;
		std::cout<<"shift last block with: "<<remainder<<" bits; result: "<<last_block<<"\n";
		
		unsigned isp_last_block(boost::lexical_cast<unsigned>(ip_.getOctet(no_blocks + 1)));
		isp_last_block >>= remainder;
		std::cout<<"shift isp_last block with: "<<remainder<<" bits; result: "<<isp_last_block<<"\n";
		
		return isp_last_block == last_block;
	}
private:
	std::string cidr_;
	std::string prefix_;
	unsigned prefix_no;
	Ipv4 ip_;
};


typedef std::multimap<unsigned, std::string> IspHit;
typedef IspHit::iterator HitIterator;

//map ISP address to name
typedef std::map<std::string, std::pair<Cidr, HitIterator> > IspMap;

IspMap isp_map;
IspHit hit_map;


//insert new ISP
void
insert(std::string const& isp_addr, std::string const& isp_name)
{
	
	HitIterator hit = hit_map.insert(std::make_pair(0, isp_name));
	isp_map.insert(std::make_pair(isp_addr, std::make_pair(isp_addr, hit)));
}

void
print()
{
	IspMap::const_iterator isp_it(isp_map.begin());
	for (; isp_it != isp_map.end(); ++isp_it)
	{
		std::cout<<isp_it->first<<" "<<isp_it->second.first.getCidr()<<" : " << isp_it->second.second->first<<"\n";
	}
}

//increment hit counter for an ISP
void
hit(IspMap::iterator& isp_it)
{
	//isp found, increment counter
	//isp_it->second.second
	unsigned val = isp_it->second.second->first;
	++val;

	hit_map.erase(isp_it->second.second);
	isp_it->second.second = hit_map.insert(std::make_pair(val, isp_it->second.first.getCidr()));
}

//display top n ISP hits
void
topHits(unsigned n)
{
	std::cout<<"top "<<n<<" ISPs:\n";
	IspHit::const_reverse_iterator hit_it(hit_map.rbegin());
	for (; hit_it != hit_map.rend() && n; ++hit_it, --n)
	{
		std::cout<<hit_it->first<<" "<<hit_it->second<<"\n";
	}
	
	std::cout<<std::endl;
}

void
test()
{
	insert("1.2.3.5/29", "ISPa");
	insert("3.4.5.6/30", "ISPb");
	insert("3.3.5.9/31", "ISPc");
	insert("192.168.20.16/28", "ISPd");
	
	typedef std::vector<std::string> IpList;
	IpList ip_list;
	ip_list.push_back("1.2.3.0");
	ip_list.push_back("1.2.3.1");
	ip_list.push_back("1.2.3.2");
	ip_list.push_back("1.2.3.3");
	ip_list.push_back("1.2.3.4");
	ip_list.push_back("1.2.3.5");
	ip_list.push_back("1.2.3.12");
	ip_list.push_back("1.2.3.15");
	ip_list.push_back("192.168.20.19");
	ip_list.push_back("192.168.20.15");
	ip_list.push_back("192.168.20.33");
	ip_list.push_back("192.168.20.32");
	
	IpList::const_iterator cip(ip_list.begin());
	for (; cip != ip_list.end(); ++cip)
	{
		IspMap::iterator isp_it(isp_map.begin());
		for (; isp_it != isp_map.end(); ++isp_it)
		{
			if (isp_it->second.first.matchesIp(*cip))
			{
				hit(isp_it);
				std::cout<<"HIT \n-------------------------------------------\n";
		
				break;
			}
		}
	}
	
	print();
	
	topHits(0);
	topHits(1);
	topHits(2);
}


int main()
{
	test();
	return 0;
}
