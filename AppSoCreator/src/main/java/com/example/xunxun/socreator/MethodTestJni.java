package com.example.xunxun.socreator;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

import java.lang.ref.WeakReference;

/**
 * Created by xunxun on 2018/3/6.
 */

public class MethodTestJni {
    String TAG = "MethodTestJni_xunxun";
    private EventHandler<Context> mEventHandler;
    public MethodTestJni(Context context) {
        mEventHandler = new EventHandler<Context>(context, context.getMainLooper());
    }

    public native String method_test1();
    public native boolean method_test100(byte[] bytes, int i);

    public static native String method_test2(String str);

    public native int method_test3(int num);

    public native long method_test4(long str);

    public native double method_test5(double str);

    public native float method_test6(float str);


    public native void method_test7(String str, int num);

    public native void method_test8(String str, int[] numArr);

    public native String[] method_test9();

    public native MethodTestInternal method_test11(MethodTestInternal str);

    public native boolean sqlite3_open(String path);

    public native void method_testCallback();

    public static class MethodTestInternal {
        public String str;
        public int num;

        public MethodTestInternal(String str, int num) {
            this.str = str;
            this.num = num;
        }

        @Override
        public String toString() {
            return "MethodTestInternal{" +
                    "str='" + str + '\'' +
                    ", num=" + num +
                    '}';
        }
    }


    private static class EventHandler<T> extends Handler {
        private final WeakReference<T> ref;

        public EventHandler(T t, Looper looper) {
            super(looper);
            ref = new WeakReference<T>(t);
        }
    }


    private static void postEventFromNative(Object weakThiz, int what,
                                            int arg1, int arg2, Object obj) {
        if (weakThiz == null)
            return;

        MethodTestJni methodTestJni = (MethodTestJni) ((WeakReference) weakThiz).get();
        if (methodTestJni == null) {
            return;
        }

        if (methodTestJni.mEventHandler != null) {
            Message m = methodTestJni.mEventHandler.obtainMessage(what, arg1, arg2, obj);
            methodTestJni.mEventHandler.sendMessage(m);
        }
    }


    /**
     * Default library loader
     * Load them by yourself, if your libraries are not installed at default place.
     */
    private static final IjkLibLoader sLocalLibLoader = new IjkLibLoader() {
        @Override
        public void loadLibrary(String libName) throws UnsatisfiedLinkError, SecurityException {
            System.loadLibrary(libName);
        }
    };

    private static volatile boolean mIsLibLoaded = false;

    public static void loadLibrariesOnce(IjkLibLoader libLoader) {
        synchronized (MethodTestJni.class) {
            if (!mIsLibLoaded) {
                if (libLoader == null)
                    libLoader = sLocalLibLoader;

                libLoader.loadLibrary("methodTest");
                mIsLibLoaded = true;
            }
        }
    }

    public interface IjkLibLoader {
        void loadLibrary(String libName) throws UnsatisfiedLinkError,
                SecurityException;
    }

    public void nativeCallback(byte[] buf, int size, int frameNum, boolean isKeyFrame, int width, int height) {
        Log.d(TAG,"nativeCallback buf:"+buf+" size:"+size);

    }
//public void nativeCallback(byte[] buf,int i) {
//    Log.d(TAG,"nativeCallback");
//}
}
