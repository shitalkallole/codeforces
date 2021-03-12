	bool got=true;
	for(auto it=required.begin();it!=required.end();it++){
		if((it->second).size()!=0){
			got=false;
			break;
		}
	}