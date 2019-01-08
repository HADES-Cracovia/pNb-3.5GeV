void read_hist(char* plik)
{
  TFile *MyFile = new TFile("plik","READ");
  if ( MyFile->IsOpen() ) printf("File opened successfully\n");

  TFile *save=new TFile(
}
