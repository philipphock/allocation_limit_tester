#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>

using std::cout;
using std::endl;

bool alloc(unsigned long long size){
		try{
			char *alloc = new char[size];
			delete[] alloc;
		}catch(const std::bad_alloc& a){
			return false;
		}
		
		return true;
	
}

int main (int argc, char* argv[]){
		
		
	unsigned long long maxMemory = 100000000000;
	
	
	unsigned long long lower = 100000000000;
	unsigned long long upper = 100000000000;
	bool asc = false;
	
	//calc lower bound
	while(!alloc(maxMemory)){
		maxMemory/=10;
	}
	lower = maxMemory;
	
	//calc upper bound
	while(alloc(maxMemory)){
		maxMemory*=2;
	}
	upper = maxMemory;
	
	int stp=100;
	
	while(true){
		
		if (std::abs(upper-lower)<2){
			break;
		}
		if (stp==0){
			cout << "max iteration level reached.. "<<endl;
			cout << "I can guess your allocation limit within those bounds:"<<endl;
			cout << "upper bound: " << upper<<endl;
			cout << "lower bound: " << lower<<endl;;
			return 0;
		}
		stp--;
		
		//cout << "try: "<<maxMemory<<": ";
		if (asc){
			//cout << "ASC ";
			if (alloc(maxMemory)){
				//cout << "ok"<<endl;
				if (lower<maxMemory){
					lower=maxMemory;
					//cout << "switch lower bound to " << lower  << endl;
				}
				maxMemory=(upper+maxMemory)/2;
				
				
			}else{
				asc=false;
				//cout << "fail, switch to desc"  << endl;
				if (upper>maxMemory){
					upper=maxMemory;
					//cout << "switch upper bound to " << upper  << endl;
				}
			}
			
		}else{
			//cout << "DESC ";
			if (alloc(maxMemory)){
				asc=true;
				//cout << "ok, switch to asc"<<endl;
				if (lower<maxMemory){
					lower=maxMemory;
					//cout << "switch lower bound to " << lower  << endl;
				}
			}else{
				//cout << "fail"<<endl;
				if (upper>maxMemory){
					upper=maxMemory;
					//cout << "switch upper bound to " << upper  << endl;
				}
				maxMemory=(lower+maxMemory)/2;
				
				
			}
		}
		
		
		
	}
	
	
	cout << "I can allocate a maximum of  "<<lower<<" byte" <<endl;
	std::stringstream s;
	std::stringstream out;
	
	s<<lower;
	unsigned long j=0;
	for (long i=s.str().length()-1;i>=0;i--){
		
		if (j%3==0){
			out<<" ";
		}
		out<<s.str()[i];
		
		j++;
	}
	
	
	std::string outR;
	outR = out.str();
	
	
	std::reverse(outR.begin(), outR.end());
	cout << outR<<endl;
	
	
	
	return 0;
}
