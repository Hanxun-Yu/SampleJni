#include <stdio.h>
#include <stdlib.h>

#include "https.h"

#define MAX_BUFFER_SIZE    (1024 * 1024)    /* 1MB */

int main() {
    char *resp = malloc(MAX_BUFFER_SIZE);
    //char *body = malloc(MAX_BUFFER_SIZE);

//	int n = https_send_request(GET, "www.kernel.org", 443, "index.html", resp, MAX_BUFFER_SIZE);
//	resp[n] = 0;

//	printf("%s\n", resp);

    //n = http_send_request(GET, "www.baidu.com", 80, "index.html", resp, MAX_BUFFER_SIZE);
    char *authstr = "g8s3sb2tebnFko1OCYqGj8ejcZS4CVV%2FrVLacbpBGBeBS%2FlQeDfpMYAqWhZrQ3BaPTv3G3ZpX5uYJ2YpezJuwvp9a0fEjZYBEbgJ9SExcxCGQUZWsy%2BZfI6PMyo7hH2ivGdpMh0PcOPYwHi%2BpKkEiaQdFGa2n9DU2Zo7SwUjfGNyC5Mly%2F%2Fs%2FwGmPbYXBBN%2Fui2R0kOi%2FJOK1oFj0w8H9Xaoxwg7hEZrurygvBrDBn8C3AIiuvnuVql20hkaT5aRVUOHW8zQLNKlqOtsnJ5IUll4WVNKqCqFe4XJXaNNvGVSakjllqAp7CrSCf%2FdLwWlQagDoesVK5JF6Bxn5LaiR0wde4F5tC19AwfyXDHTxia2iTVBn4DAf755iyGDwo1LKGSMH5wzKzwcHw6ueV8oNxJKgXm2zYRAyX1MbBKEYsKBuFhI0rpM0m6PX5UPqgGtoEwrkZ8m4SLfVkz1%2F9ktLybseODoMogtdXtpAidAzIAVm6q68h%2B%2BW53hVYf18B3YHWOKwREzYRZM0kaDOmYOw%2FBgN0zUwJfDEY8BEVqwmIQAS8iZWTL51RsWWTiP9on5C1tqrHE6ZwYj67VMWcDH8I1KeCK7MUKZ1jJeKmk%2FgxZT%2B9%2BbIpQ7DR7euTJUUfNtLS6g1pJavW6umyEMo2lhoCciue2QO8qmB4hCPkxBXo%2FivpgPrI13qHhFOb4O2CMAYEPsVdp3Zf0rmb%2Bym%2BGt2pmf7OsOGjMLPV3qXDmSwgOZvs%2FPO0y23jf77iQy%2FB0n7%2FYGeKjX8ZFboP1aCJ3b5qGQ1%2B%2BYifPyZnu0TtDZeZmlPJ1eL2w5gMdPS%2B7oh2A%2BhbFb03ma9T0%2Fi3j3HPR0g94Pmmtfgd%2BCGTvBvcfZ4tN6SsX5cqrklbv3iMxjB8PRTrkr2LsSyC9NgCdAGORRdWX%2BCmgK7vkFcpFcYbPIF02bh08zU164H9eKB91MQCw4u9YjZbEZgphNNLxVB24Mub0CT7BsTowJGb6MwUEDRYdzmyoMFhOEVjBR2MCB80C%2FXqaz3v1Qi25Ip8Nshzc0NkoekJewY54uJfTPLQX3SfOYqX23owN0M%2B8S4bs14nFLbJnKJrYJTNydUSOUR7erNbORPyBq1UypPtE5ZCgjbVeSxNBuFlo3KVjkVmjQ9qBIGgiBBeTajPHCWcYCdYav%2Bi1oEQeelqOWak31ghUyJi5XGDVPr8MFWZFfQIoLqPmhbFhxAbIHTah28scm7GmEn%2F35TK7NFB7yvMhFZpMu%2BkKo6689yE9CJYeuTVSe8aYHNX2WbwnWAACXNVhzmjzwaCoYagWAKhi5Qs1GvXafRGQRZR8ABRmFk0YpAz5HQUr5UMGzMtDLunLOlmRXCmy3%2F4rNAnsp5twmZC5NuHQo5kitK94s4AD1rIYjJ0qI7Wba4zed4VMn66LoEaMqGf0TLkLdSOX1BWatdo9yHkrqkyhXGphCUlOjE1jRAKbVnCV6dddlb8IUpCPhL7uwpM86vArICRFKgikflM8WvkaRWYejfCwM1UQfG66dYz0SogV3GcBRMUrexIKqYE6kgkvXgMHs5qdPt7uwEcDPuRMc2uospel%2F%2BEY0FLD1XCYVILo0HufVyegnn%2FlqfqTfWCGLHNV%2B%2BFnYAvBAmTnrYitO7mEQdH%2BmRvTwDh0ilmp6eiNDFFYdhZVbbPmxXAFO3usBnkHHwTO728acLBvo4cYMcnO9bM6S7GwO9se%2F1NJQyYewbl8mDsIfc2Ra775TCgY6lKtrp6Cv6MXiP4juiXiKBuTvmnvOd0YR0huce6G5b7EAh%2BFOCMCHGTQ9uAF8zpDzMblibIfHbCfB8L2cV8t4MYcvyT7aufCPZdcailax0GkkgOmHvoDTEtWXpl5ATQNh%2BO3CmnalKfEMyJkaC0LSpNUULLoIdBA%2F9JRlBFq2uOXVmSe9nypFptILTFK%2FDHtirkxzsYmSd1in6nDI7JYzXkDAmu6qi5L4l%2BRnG%2FO0Y14PidFmk%2B6WME4m14SN0YCq2DBCOhJ918Z72GLgl3SnvNI7VUL6qx1gcVbsrIBDMx2e7z6tB4tQvwdeNh8Z%2FA%2Ff5GPrz340Zxonjx1sFXwg%2B0cMYqwtrX9X6ne4FSTWXjHdsyBRCuHNhi47UYVU2ahAHUjVUORY9eZgGzqI3VyaBfbH5sBUIeIPmn6QiNOWTjOeGqYQjIdLY4yg8xj0dXcE6Lhv%2Bkf3SfCtCMAmjkU7hfZu5L6o1foIQhl%2FpbRHJ7TA0oeBifUnmuTWfPzg9IJy3Qcvo14QKz7e%2B67zY5%2FQyW2%2Btw9gv55Zl2l5iyX3YB0TCLpsCDlPQPixvp%2BhbBgkA0wwmwWD0JYlsFseudkgTM5Tlwtbmf8T%2FcBzC2sguHZ0BBjrzWmqdTqt0kYwxiUVk%2FZSsAaB%2Bmg6jkLXibiJ2TeoKU7PDEjru%2Fg4TignmsyZEGg%2B1gOmFagol6rLZ7rMAuaHnDADDjNNLSyvCCc2Mr%2FtZHhkaScd4Trcnmh5AsHBObZFboYc6jbW7D%2F9AwFYl%2FSeCuAk6Y%2F5VqJ2gUwVRhB70Y%2FX7wl87dg6oEpSKbFeSPKpw3i2eaYIIN9IMDA1zTEOj19WPsN5T3PN3kKpbqFgx%2FFhhgS2TfQTGZEmYb5J%2FAAaWOwSUmc03PFJQJ0bwV3R2Jd9ew53ILr39OP91j1cieLvrydRQOKNoZ7cKMm2s8qlM4uoKtoZ%2BferO2Sxer8h0J1gPuCOjIRPxD6YJM%2BTbwAkeWHTN3XzjjVtyeS0Ddez0wdMr%2F%2FNDfAQ3OOaMwDhtG8J8eUeI64oaRsKsyZpo9FCMQzxy8puBxS0ynxCNiItuxi%2BLHDAwli6WIAqmIcBwgXKC5klgu2Y1og00Gx%2Br19CTMXD%2BWYM2G%2FtqUSLTwBJD5q3d93N52hGtIceq%2FKEGD9ArNmUOfhLsk%2BRyeU420Dx9nxnANqZF%2ByC0gvzCLOv%2BJ6X11fxTXhudfy4jc%2BnipcbltWkPwDHQ5PJ%2BNpT0Bo2G0LG4I1TeWPRjFK1BV%2BFrkuNWJ4RD2lyQ3IH4nBHySQUHw6dz4HCvI5c9mKEwKesBwsl5A17R4CVt2hshSEZyMwsdaMdXiyHytnOxnOk8XupnF7D%2BUIuT5C%2Bifby9B3N7CzNqRkrRiwVF4w4lDNNewEYKS2ipemBWwXw%2Bww%2BlSsmNgtYrYTNdFWZjNFuR6pTM%2Fw64HqTUIUuHtYKRPZQniDdo6%2BINcu21AtS3uDoUB37oC39sJPwAMSn2XZj67oSerW8%2BT0uDBJcwgjz7wFdl6aD632YURh0cEdACqkUFgfExjEOvc6%2FoI%2BjMVOB4RACU%2FbGVMiK%2F6zTh9l5enXCbxGxcD9e%2FVjywxTVz0R4hr0exvhzVbHPEFE6GL8jkOcmdiUF81TPCGpFJosohf%2FdxtYLwD9Xzzk2FII8Qfrao52WVxRgL%2Btu0LhSf7wKP4hWfyTTEzXm5woKKkNUkKk01%2B6IpCqBgm5o8Tg1YhyKRRqdAM73oVa5SiYMC64LazMK09kLgkKheRHYYnPq6pWb7M1XQGfhbBeh6Fb1qka659z9O5dMqD5BnlqQgG8%3D&auth_duration=30&api_key=Rpfc0ckNfodszTKZWJIST02Ur0LN09sf&api_secret=YtJlRCxWWABqTWfW9KaJfC8sy0wYProp";
    int n = https_send_request(POST, "api-cn.faceplusplus.com", 443, "/sdk/v3/auth", "", resp,
                               MAX_BUFFER_SIZE);

    resp[n] = 0;

    printf("n=%d\n,%s\n", n, resp);

    free(resp);

    return 0;
}
