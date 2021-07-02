
//https://stackoverflow.com/questions/25540547/how-to-download-a-zip-file-from-server-using-curl-in-c
#define CURL_STATICLIB
#include <stdio.h>
#include <curl/curl.h>
//#include <curl/types.h>
#include <curl/easy.h>
#include <string.h>
#include <stdlib.h>

#define false 0

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(void) {
    CURL *curl;
    FILE *fp;
    CURLcode res;

    const char url[] = "https://github.com/MrPoudel/cmake-example/archive/refs/heads/master.zip";
    const char outfilename[FILENAME_MAX] = "./test.zip";

    curl_version_info_data * vinfo = curl_version_info(CURLVERSION_NOW);

    if(vinfo->features & CURL_VERSION_SSL){
        printf("CURL: SSL enabled\n");
    }else{
        printf("CURL: SSL not enabled\n");
    }

    curl = curl_easy_init();
    if (curl) {
        fp = fopen(outfilename,"wb");        

        /* Setup the https:// verification options. Note we   */
        /* do this on all requests as there may be a redirect */
        /* from http to https and we still want to verify     */
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, url);
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        // curl_easy_setopt(curl, CURLOPT_CAINFO, "./github-com.pem");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);

        if(res == CURLE_OK)
            printf("Download successful\n");
        else
            printf("ERROR: %s\n", curl_easy_strerror(res));

        curl_easy_cleanup(curl);
        curl_global_cleanup();

        if(!fclose(fp))
            system("unzip test.zip");
    }
    return 0;
}