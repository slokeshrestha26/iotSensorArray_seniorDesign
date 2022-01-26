package com.cloudmd365.rae.util;

import java.util.ArrayList;
import org.apache.commons.lang3.ArrayUtils;

public class ClassifyDataUtil {
    // static { System.loadLibrary("data_classify"); }
    public int classifyData(ArrayList<Double> data){
        double[] arr = ArrayUtils.toPrimitive(data.toArray(new Double[0]));
        return classify_data(arr);
    }
    public native int classify_data(double[] data);
    public native String initLibrary();
}