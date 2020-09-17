/*
 * Copyright (C) 2012 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package android.renderscript.cts;

import com.android.cts.stub.R;
import android.renderscript.Allocation;
import android.renderscript.RSRuntimeException;

public class AtanTest extends RSBaseCompute {
    private ScriptC_atan_f32 script_f32;
    private ScriptC_atan_f32_relaxed script_f32_relaxed;

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        script_f32 = new ScriptC_atan_f32(mRS);
        script_f32_relaxed = new ScriptC_atan_f32_relaxed(mRS);
    }

    @Override
    public void forEach(int testId, Allocation mIn, Allocation mOut) throws RSRuntimeException {
        switch (testId) {
        case TEST_F32:
            script_f32.forEach_atan_f32_1(mIn, mOut);
            break;
        case TEST_F32_2:
            script_f32.forEach_atan_f32_2(mIn, mOut);
            break;
        case TEST_F32_3:
            script_f32.forEach_atan_f32_3(mIn, mOut);
            break;
        case TEST_F32_4:
            script_f32.forEach_atan_f32_4(mIn, mOut);
            break;

        case TEST_RELAXED_F32:
            script_f32_relaxed.forEach_atan_f32_1(mIn, mOut);
            break;
        case TEST_RELAXED_F32_2:
            script_f32_relaxed.forEach_atan_f32_2(mIn, mOut);
            break;
        case TEST_RELAXED_F32_3:
            script_f32_relaxed.forEach_atan_f32_3(mIn, mOut);
            break;
        case TEST_RELAXED_F32_4:
            script_f32_relaxed.forEach_atan_f32_4(mIn, mOut);
            break;
        }
    }

    @Override
    protected float[] getRefArray(float[] in, int input_size, int stride, int skip) {
        float[] ref = new float[input_size * stride];
        for (int i = 0; i < input_size; i++) {
            for (int j = 0; j < stride - skip; j++) {
                int idx= i * stride + j;
                int idxRef = i * (stride - skip) + j;
                ref[idxRef] = (float)(Math.atan((double)in[idx]));
            }
        }
        return ref;
    }

    public void testAtanF32() {
        doF32(0x12a, 5);
    }

    public void testAtanF32_relaxed() {
        doF32_relaxed(0x12a, 128);
    }

    public void testAtanF32_2() {
        doF32_2(0xad, 5);
    }

    public void testAtanF32_2_relaxed() {
        doF32_2_relaxed(0xad, 128);
    }

    public void testAtanF32_3() {
        doF32_3(0xafe, 5);
    }

    public void testAtanF32_3_relaxed() {
        doF32_3_relaxed(0xafe, 128);
    }

    public void testAtanF32_4() {
        doF32_4(0x1238, 5);

    }
    public void testAtanF32_4_relaxed() {
        doF32_4_relaxed(0x1238, 128);
    }

}
