int main(){
	FILE*fp
	char *str;
	char tval1,tval2,tval3,tval4;
	size_t num_of_bytes = 6;
	int Bled,Btast;
	while(1){
		fp = fopen("/dev/led","w");
		if(fp == NULL){
			printf("problem");
			return -1;
		}

		fputs("0x00\n", fp);
		if(fclose(fp)){
			printf("Problem pri zatvaranju /dev/led\n");
			return -1;
		}
	
		//Citanje vrednosti dioda
		fp =fopen("/dev/led", "r");
		if(fp==NULL) {
			puts("Problem pri otvaranju /dev/led");
			return -1;}

		str = (char *)malloc(num_of_bytes+1);
		getline(&str, &num_of_bytes, fp);
		if(fclose(fp)){
			puts("Problem pri zatvaranju /dev/led");
			return -1;}

		tval1 = str[2] - 48;
		tval2 = str[3] - 48;
		tval3 = str[4] - 48;
		tval4 = str[5] - 48;
		free (str);
		bled = (tval1*pow(2,3))+(tval2*pow(2,2))+(tval3*(pow(2,1))+tval4


		//Citanje vrednosti tastera
		fp = fopen("/dev/button", "r");
		if(fp==NULL) {
			puts("Problem pri otvaranju /dev/button");
			return -1;}
		str = (char *)malloc(num_of_bytes+1);
		getline(&str, &num_of_bytes, fp);
		if(fclose (fp)){
			puts("Problem pri zatvaranju /dev/button");
			return -1;}

		tval1 = str[2] - 48;
		tval2 = str[3] - 48;
		tval3 = str[4] - 48;
		tval4 = str[5] - 48;
		free(str);

		Btast = (tval1*pow(2,2))+(tval2*2)+tval3;

		if(tval4 == 1){
			
		
	}
}
