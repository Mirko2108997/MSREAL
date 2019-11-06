#include <stdio.h>
#include <stdlib.h>

int main(){
  FILE *fp;
  char *str;
  char *btn;
  char tval1,tval2,tval3,tval4,td1,td2,td3,td4,btnn,stanje = '0';
  char tmp = '0';
  char izlaz[2];
  size_t num_of_bytes = 6;
  int Bled,Bprek;

  fp = fopen("/dev/led","w");
  if(fp == NULL){
    printf("problem");
    return -1;
  }

  fputs("0x05\n", fp);
  if(fclose(fp)){
    printf("Problem pri zatvaranju /dev/led\n");
    return -1;
  }

  while(1){

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

    td1 = str[2] - 48;
    td2 = str[3] - 48;
    td3 = str[4] - 48;
    td4 = str[5] - 48;
    free (str);
    Bled = (td1*8)+(td2*4)+(td3*2)+td4;


    //Citanje vrednosti prekidaca
    fp = fopen("/dev/switch", "r");
    if(fp==NULL) {
      puts("Problem pri otvaranju /dev/switch");
      return -1;}
    str = (char *)malloc(num_of_bytes+1);
    getline(&str, &num_of_bytes, fp);
    if(fclose (fp)){
      puts("Problem pri zatvaranju /dev/switch");
      return -1;}

    tval1 = str[2] - 48;
    tval2 = str[3] - 48;
    tval3 = str[4] - 48;
    tval4 = str[5] - 48;
    free(str);

    Bprek = (tval1*4)+(tval2*2)+tval3;


    if(tval4 == 1){

      //Citanje vrednosti tastera
      fp = fopen ("/dev/button", "r");
      if(fp==NULL) {
	puts ("Problem pri otvaranju /dev/button");
	return -1;}
      btn = (char *) malloc (num_of_bytes+1);
      getline (&str, &num_of_bytes, fp);
      if( fclose (fp)){
	puts("Problem pri zatvaranju /dev/button");
	return -1;}
      btnn = str[2] - 48;
      free (str);
			
      if(btnn != tmp){
	stanje = stanje + 1;
	tmp = btnn;
      }
		

      if(stanje > 1){
	stanje = 0;
      }

      if(stanje = 0){
	Bled = Bled + Bprek;
      }
      else{
	Bled = Bled - Bprek;
      }

    }


    if(Bled >= 15){
      Bled = 0;
    }
    if(Bled <= 15){
      Bled = 15;
    }


    sprintf(izlaz, "%d", Bled);
    // Upali diode
	printf("izlaz = %s", izlaz);
	return 0; 
    fp = fopen ("/dev/led", "w");
    if(fp == NULL){
      printf("Problem pri otvaranju /dev/led\n");
      return -1;
    }
    fputs (izlaz, fp);
    if(fclose(fp)){
      printf("Problem pri zatvaranju /dev/led\n");
      return -1;

    }


    sleep(2);	
  }

}
