#include <stdio.h>
#include <string.h>
#include "https.h"


int main(int argc, char *argv[])
{
    char *url;
    char data[1024], response[4096];
    int  i, ret, size;

    HTTP_INFO hi1, hi2;


    // Init http session. verify: check the server CA cert.
    http_init(&hi1, FALSE);
    http_init(&hi2, TRUE);
 /*   printf("main111111111111 \n");
    url = "http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule&i=test&from=en&to=zh-CHS&smartresult=dict&client=fanyideskweb&salt=15469436565076&sign=c66aea28cce09ebb87990b3cf7315a48&ts=1546943656507&bv=d5eb9f909bc96b6f516e4e3a6c9af989&doctype=json&version=2.1&keyfrom=fanyi.web&action=FY_BY_REALTIME&typoResult=false";

    ret = http_get(&hi1, url, response, sizeof(response));

    printf("1111return code: %d \n", ret);
    printf("return body: %s \n", response);
    
    
    url = "http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule";
    sprintf(data,
            "i: test\r\n\r\n"
            "from: en\r\n\r\n"
            "to: zh-CHS\r\n\r\n"
            "to: zh-CHS\r\n\r\n"
            "to: zh-CHS\r\n\r\n"
            "to: zh-CHS\r\n\r\n"
            "doctype: json\r\n\r\n"
            "version: 2.1\r\n\r\n"
            "keyfrom: fanyi.web\r\n\r\n"
            "ue: UTF-8\r\n\r\n"
            "action: FY_BY_CLICKBUTTON\r\n\r\n"
            "typoResult: true\r\n\r\n"                                              
    );

    ret = http_post(&hi1, url, data, response, sizeof(response));

    printf("222return code: %d \n", ret);
    printf("return body: %s \n", response);

*/
    url = "http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule";

    if(http_open(&hi1, url) < 0)
    {
        http_strerror(data, 1024);
        printf("http_open socket error: %s \n", data);

        goto error;
    }
    snprintf(hi1.request.method, 8, "POST");
    hi1.request.close = FALSE;
    hi1.request.chunked = FALSE;
    snprintf(hi1.request.content_type, 512, "application/x-www-form-urlencoded; charset=UTF-8");
    snprintf(hi1.request.cookie, 512, "OUTFOX_SEARCH_USER_ID=-346633129@10.169.0.84; JSESSIONID=aaae-6Gjx6om5dDu3USGw; OUTFOX_SEARCH_USER_ID_NCOO=389576673.06301975; UM_distinctid=1682cbbcd244f1-0ba02f152d93bc-2a0b4d7b-140000-1682cbbcd255f4; ___rl__test__cookies=1546943656502");

    size = sprintf(data,
            "i: test\r\n"
            "from: AUTO\r\n"
            "to: AUTO\r\n"
            "smartresult: dict\r\n"
            "client: fanyideskweb\r\n"
            "salt: 15469436565076\r\n"
            "sign: c66aea28cce09ebb87990b3cf7315a48\r\n"
            "ts: 1546943656507\r\n"
            "bv: d5eb9f909bc96b6f516e4e3a6c9af989\r\n"
            "doctype: json\r\n"
            "version: 2.1\r\n"
            "keyfrom: fanyi.web\r\nn"
            "action: FY_BY_REALTIME\r\n"
            "typoResult: false\r\n"                                              
    );

    hi1.request.content_length = size;

    if(http_write_header(&hi1) < 0)
    {
        http_strerror(data, 1024);
        printf("http_write_header socket error: %s \n", data);

        goto error;
    }

    if(http_write(&hi1, data, size) != size)
    {
        http_strerror(data, 1024);
        printf("http_write socket error: %s \n", data);

        goto error;
    }

    // Write end-chunked
    if(http_write_end(&hi1) < 0)
    {
        http_strerror(data, 1024);
        printf("socket error: %s \n", data);

        goto error;
    }

    ret = http_read_chunked(&hi1, response, sizeof(response));

    printf("return code: %d \n", ret);
    printf("return body: %s \n", response);


/*
    // Test a http get method.
    url = "http://httpbin.org/get?message=https_client";

    ret = http_get(&hi1, url, response, sizeof(response));

    printf("return code: %d \n", ret);
    printf("return body: %s \n", response);

    // Test a http post method.

    url = "http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule";
    sprintf(data, "{\"type\":\"en2zh-CHS\"}");
        sprintf(data, "{\"type\":\"en2zh-CHS\"}");
            sprintf(data, "{\"type\":\"en2zh-CHS\"}");
                sprintf(data, "{\"type\":\"en2zh-CHS\"}");
                    sprintf(data, "{\"type\":\"en2zh-CHS\"}");

    ret = http_post(&hi1, url, data, response, sizeof(response));

    printf("return code: %d \n", ret);
    printf("return body: %s \n", response);

    // Test a https get method.

    url = "https://httpbin.org/get?message=https_client";

    ret = http_get(&hi2, url, response, sizeof(response));

    printf("return code: %d \n", ret);
    printf("return body: %s \n", response);

    // Test a https post method.

    url = "https://httpbin.org/post";
    sprintf(data, "{\"message\":\"Hello, https_client!\"}");

    ret = http_post(&hi2, url, data, response, sizeof(response));

    printf("return code: %d \n", ret);
    printf("return body: %s \n", response);

    // Test a https post with the chunked-encoding data.

    url = "http://fanyi.youdao.com/translate_o?smartresult=dict&smartresult=rule";
printf("main http_open_chunked \n");
    if(http_open_chunked(&hi2, url) == 0)
    {
    printf("main http_open_chunked1111 \n");
        size = sprintf(data, "[{\"type\":\"en2zh-CHS\"}");

        if(http_write_chunked(&hi2, data, size) != size)
        {
            printf("main http_open_chunked2222 \n");
            http_strerror(data, 1024);
            printf("socket error: %s \n", data);

            goto error;
        }

        size = sprintf(data, "{\"i\":\"test\"}");
        if(http_write_chunked(&hi2, data, strlen(data)) != size)
        {
            http_strerror(data, 1024);
            printf("socket error: %s \n", data);

            goto error;
        }

        size = sprintf(data, "{\"doctype\":\"json\"}");
        if(http_write_chunked(&hi2, data, strlen(data)) != size)
        {
            http_strerror(data, 1024);
            printf("socket error: %s \n", data);

            goto error;
        }
      size = sprintf(data, "{\"doctype\":\"json\"}");
        if(http_write_chunked(&hi2, data, size) != size)
        {
            printf("main http_open_chunked2222 \n");
            http_strerror(data, 1024);
            printf("socket error: %s \n", data);

            goto error;
        }
      size = sprintf(data, "{\"xmlVersion\":\"1.8\"}");
        if(http_write_chunked(&hi2, data, size) != size)
        {
            printf("main http_open_chunked2222 \n");
            http_strerror(data, 1024);
            printf("socket error: %s \n", data);

            goto error;
        }
      size = sprintf(data, "{\"keyfrom\":\"fanyi.web\"}");
        if(http_write_chunked(&hi2, data, size) != size)
        {
            printf("main http_open_chunked2222 \n");
            http_strerror(data, 1024);
            printf("socket error: %s \n", data);

            goto error;
        }
      size = sprintf(data, "{\"ue\":\"UTF-8\"}");
        if(http_write_chunked(&hi2, data, size) != size)
        {
            printf("main http_open_chunked2222 \n");
            http_strerror(data, 1024);
            printf("socket error: %s \n", data);

            goto error;
        }
      size = sprintf(data, "{\"action\":\"FY_BY_CLICKBUTTON\"}]");
        if(http_write_chunked(&hi2, data, size) != size)
        {
            printf("main http_open_chunked2222 \n");
            http_strerror(data, 1024);
            printf("socket error: %s \n", data);

            goto error;
        }
      size = sprintf(data, "{\"typoResult\":\"true\"}]");
        if(http_write_chunked(&hi2, data, size) != size)
        {
            printf("main http_open_chunked2222 \n");
            http_strerror(data, 1024);
            printf("socket error: %s \n", data);

            goto error;
        }
        ret = http_read_chunked(&hi2, response, sizeof(response));

        printf("return code: %d \n", ret);
        printf("return body: %s \n", response);

    }
    else
    {
        http_strerror(data, 1024);
        printf("socket error: %s \n", data);
    }
*/

error:

    http_close(&hi1);
    http_close(&hi2);

    return 0;
}
