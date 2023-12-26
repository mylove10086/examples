/**
 * Created by IBM on 2021/7/26.
 */
#include <stdio.h>
#include <curl/curl.h>
#include <zlib.h>


int main(void) {

    unsigned char szSrc[] = "test the compression and uncompression of zlib.";
    unsigned long nSrcLen = sizeof(szSrc);

    unsigned char szZip[1024] = {0};
    unsigned long nZipLen = 1024;

    compress(szZip, &nZipLen, szSrc, nSrcLen);

    //
    unsigned char szUnZip[1024] = {0};
    unsigned long nUnZipLen = 1024;

    uncompress(szUnZip, &nUnZipLen, szZip, nZipLen);
    CURL *curl;
    CURLcode res;

    char *v = curl_version();
    printf("%s\n", v);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com/");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //设置ssl验证
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");

        /* Perform the request, res will get the return code */
        res = curl_easy_perform(curl);
        /* Check for errors */
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));

        /* always cleanup */
        curl_easy_cleanup(curl);
    }

    return 0;
}

