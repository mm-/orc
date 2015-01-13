#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <string.h>


int main ( int argc, char **argv )
{
  char *avalue = NULL;
  char *apicall = NULL;
  int index;
  // int a;
  int c;

  opterr = 0;

  while ((c = getopt (argc, argv, "a:")) != -1)
    switch (c)
      {
      case 'a':
	// Set the value of -a to optarg
	avalue = optarg;
	// Print arg right after api key for debugging
	printf ("other option: %s\n", argv[3]);
	// Set value of arg after api key to apicall
	apicall = argv[3];
	break;
      case '?':
	if (optopt == 'c')
	  fprintf (stderr, "Usage: `-%c` API_KEY\n", optopt);
	else
	  fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
	return 1;
      default:
	abort ();
      }
  // Print api_key for debugging
  //printf ("API_KEY = %s\n", avalue);

  if (*avalue != 0)
    {
      CURL *curl;
      CURLcode res;
      
      // Define new char str with size of 100
      // concat it with the characters api_key=
      // concat it with the char avalue
      char str[42] = "";
      strcat(str, "api_key=");
      strcat(str, avalue);
     
      // print concatted string for debugging
      //printf ("concat = %s\n", str);

      curl = curl_easy_init();
      if(curl) {
	curl_easy_setopt(curl, CURLOPT_URL, "https://api.objectrocket.com/spaceusage/get");
	// Add api key as post data to the request
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, str);
	// Show verbose curl info for debug
	//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
	/* Perform the request, res will get the return code */
	res = curl_easy_perform(curl);
	/* Check for errors */
	if(res != CURLE_OK)
	  fprintf(stderr, "curl_easy_perform() failed: %s\n",
		  curl_easy_strerror(res));

	/* always cleanup */
	curl_easy_cleanup(curl);
      }
      return 0;
    }




}

  
