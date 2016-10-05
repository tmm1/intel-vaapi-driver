/*
 * Copyright (C) 2016 Intel Corporation. All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
 * IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
 * ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "i965_config_test.h"

namespace AVC {
namespace Decode {

VAStatus HasDecodeSupport()
{
    I965TestEnvironment *env(I965TestEnvironment::instance());
    EXPECT_PTR(env);

    struct i965_driver_data *i965(*env);
    EXPECT_PTR(i965);

    return HAS_H264_DECODING(i965) ? VA_STATUS_SUCCESS :
        VA_STATUS_ERROR_UNSUPPORTED_ENTRYPOINT;
}

VAStatus HasMVCDecodeSupport(const VAProfile& profile)
{
    I965TestEnvironment *env(I965TestEnvironment::instance());
    EXPECT_PTR(env);

    struct i965_driver_data *i965(*env);
    EXPECT_PTR(i965);

    return HAS_H264_MVC_DECODING_PROFILE(i965, profile) ? VA_STATUS_SUCCESS :
        VA_STATUS_ERROR_UNSUPPORTED_ENTRYPOINT;
}

static const std::vector<ConfigTestInput> inputs = {
    {VAProfileH264Baseline, VAEntrypointVLD,
        []{return VA_STATUS_ERROR_UNSUPPORTED_PROFILE;}},

    {VAProfileH264ConstrainedBaseline, VAEntrypointVLD, &HasDecodeSupport},
    {VAProfileH264Main, VAEntrypointVLD, &HasDecodeSupport},
    {VAProfileH264High, VAEntrypointVLD, &HasDecodeSupport},

    {VAProfileH264MultiviewHigh, VAEntrypointVLD,
        std::bind(&HasMVCDecodeSupport, VAProfileH264MultiviewHigh)},
    {VAProfileH264StereoHigh, VAEntrypointVLD,
        std::bind(&HasMVCDecodeSupport, VAProfileH264StereoHigh)},
};

INSTANTIATE_TEST_CASE_P(
    AVCDecode, I965ConfigTest, ::testing::ValuesIn(inputs));

} // namespace Decode
} // namespace AVC