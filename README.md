# mass-image-processing

Simple hassle-free image processing using OpenCV for large amount of images concurrently in C++.

This program replaces a color in a group of images concurrently. For example you can change red color to green in all
images inside a directory. This operation will be in the most possible efficient way.

Created using modern C++ 20 features to utilize concurrent and parallel programming and managing threads using
asynchronous execution and _futures_.

No manual thread handling, no locks, no mutex, no semaphore.

## Advantages

* Parallel loading of images from directory
* Parallel manipulation of images in OpenCV
* Parallel saving of images to output directory
* Ability to buffer IO
* Asynchronous
* Using _futures_
* Concurrent and parallel
* Sequential version for comparison
* No lock, mutex or semaphore
* No race conditions or deadlocks
* Simple and understandable code
* Documented code

For comparison you can see a sequential manipulation of images takes too long:

https://github.com/j-tag/mass-image-processing/assets/3483320/e59c3637-8c45-44e2-8faf-dc380ed25bd0

But when using parallel execution everything is blazing fast:

https://github.com/j-tag/mass-image-processing/assets/3483320/6591a041-aafe-4c03-838a-8b6f7108534c

## Quickstart

This project is created using *OpenCV* and *TBB* libs, so you need to have those in your `$PATH` in order to compile the
project.

After cloning repo simply run:

```shell
cmake .
make
```

Then you can find the `mass_image_processing` in your current directory.

## Usage

A minimal usage would look like this:

```shell
mass_image_processing ./imgs-in ./imgs-out
```

Where `imgs-in` is a directory containing as many as _jpeg_ images as you want and `imgs-out` is an empty directory to
put the manipulated images.

There is also two more arguments that you can pass to the binary. First one is concurrency type and second one is IO
type.

Concurrency type:

* `-p` (default) for parallel processing
* `-s` for sequential processing

IO type:

* `-nb` (default) to not use buffered IO
* `-b` to use buffered IO

Parameters order matters:

```shell
Usage: mass_image_processing <input_dir> <output_dir> [-p,-s] [-nb,-b]
    -p: parallel processing (default)
    -s: sequential processing
    -nb: non-buffered I/O (default)
    -b: buffered I/O
```

Run parallel processing with non-buffered IO (default):

```shell
mass_image_processing ./imgs-in ./imgs-out
```

or

```shell
mass_image_processing ./imgs-in ./imgs-out -p -nb
```

Run parallel processing with buffered IO:

```shell
mass_image_processing ./imgs-in ./imgs-out -p -b
```

Run sequential processing with non-buffered IO:

```shell
mass_image_processing ./imgs-in ./imgs-out -s -nb
```

Run sequential processing with buffered IO:

```shell
mass_image_processing ./imgs-in ./imgs-out -s -b
```

## Comparison

Depending on how you want to process images it will have a major effect on how your system resources will be utilized
and how much time it will take to run the job.

We will compare all 4 possibilities below with different number of images.

All images are different from each other and are high-quality 4k images which every one of them has a size around 10MB.

These benchmarks are generated in an Arch Linux pc with 20 cores and 64GB of RAM.

### 10 Images

Running with 10 images will be like this:

![](https://github.com/j-tag/mass-image-processing/blob/main/extra/images/bar-graph-10-images.svg?raw=true)

| Parallel non-buffered | Parallel buffered | Sequential non-buffered | Sequential buffered |
|-----------------------|-------------------|-------------------------|---------------------|
| 1.38 secs             | 1.46 secs         | 10.38 secs              | 10.76 secs          |

### 100 Images

Running with 100 images will be like this:

![](https://github.com/j-tag/mass-image-processing/blob/main/extra/images/bar-graph-100-images.svg?raw=true)

| Parallel non-buffered | Parallel buffered | Sequential non-buffered | Sequential buffered |
|-----------------------|-------------------|-------------------------|---------------------|
| 20.39 secs            | 20.28 secs        | 170.40 secs             | 170.22 secs         |

### 1000 Images

Running with 1000 images will be like this:

![](https://github.com/j-tag/mass-image-processing/blob/main/extra/images/bar-graph-1000-images.svg?raw=true)

| Parallel non-buffered | Parallel buffered | Sequential non-buffered | Sequential buffered |
|-----------------------|-------------------|-------------------------|---------------------|
| 131.16 secs           | 129.61 secs       | 16.99 mins              | 16.93 mins          |

### Conclusion

#### Runtime Comparison

By comparing runtime results we can see the parallel version is about 8 times faster than the sequential version.

#### Resource Usage

Sequential version used a fixed amount of CPU and RAM because every image was roughly the same size and there was no
parallel execution. Even one percent of CPU and RAM was not acquired by sequential version, so many of the system
resources was not utilized and remained useless. But on the other hand the parallel version used as much CPU and RAM as
it could acquire without degrading the performance of other parts of the system. This is because C++ asynchronous
programming will manage threads in the most efficient way possible.

#### Buffered IO

Enabling or disabling buffered IO seems to not much affect the performance, but when number of images increases it
improves the performance. So we can say for low number of images (e.g. less than 1000) it's better to use non-buffered
version but for higher amounts of images it's better to use buffered IO.
