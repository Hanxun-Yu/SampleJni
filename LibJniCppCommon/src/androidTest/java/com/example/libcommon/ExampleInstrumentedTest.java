package com.example.libcommon;

import android.content.Context;
import android.support.test.InstrumentationRegistry;
import android.support.test.runner.AndroidJUnit4;
import android.util.Log;

import org.junit.Test;
import org.junit.runner.RunWith;

import static org.junit.Assert.*;

/**
 * Instrumented test, which will execute on an Android device.
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
@RunWith(AndroidJUnit4.class)
public class ExampleInstrumentedTest {
    @Test
    public void useAppContext() {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getTargetContext();

        assertEquals("com.example.libcommon.test", appContext.getPackageName());
    }

    @Test
    public void testMain() {
        TestJnicom tji = new TestJnicom();
        tji.testJnicom("javaString", new int[]{1, 2, 3, 4, 5});

        String str = tji.testjstrValOf();
        char[] charArr = tji.testjcharValOf();
        byte[] byteArr = tji.testjbyteValOf();

        Log.d("_xunxun", "str:" + str);
        for (int i = 0; i < charArr.length; i++) {
            Log.d("_xunxun", "charArr:" + charArr[i]);
        }
        Log.d("_xunxun", "byteArr:" + new String(byteArr));
    }
}
