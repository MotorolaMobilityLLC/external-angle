deps = {
  "third_party/gyp":
      "http://chromium.googlesource.com/external/gyp@9f594095c5b14f8bc518081a660e77890c294861",

  # TODO(kbr): figure out how to better stay in sync with Chromium's
  # versions of googletest and googlemock.
  "src/tests/third_party/googletest":
      "http://chromium.googlesource.com/external/googletest.git@23574bf2333f834ff665f894c97bef8a5b33a0a9",

  "src/tests/third_party/googlemock":
      "http://chromium.googlesource.com/external/googlemock.git@b2cb211e49d872101d991201362d7b97d7d69910",

  "src/tests/third_party/deqp":
      "https://android.googlesource.com/platform/external/deqp@9b4161daf7defa4d0ee7e88df886b284d1becf43",

  "src/tests/third_party/libpng":
      "https://android.googlesource.com/platform/external/libpng@094e181e79a3d6c23fd005679025058b7df1ad6c",

  "src/tests/third_party/zlib":
      "https://chromium.googlesource.com/chromium/src/third_party/zlib@afd8c4593c010c045902f6c0501718f1823064a3",
}

hooks = [
  {
    # A change to a .gyp, .gypi, or to GYP itself should run the generator.
    "pattern": ".",
    "action": ["python", "build/gyp_angle"],
  },
]
