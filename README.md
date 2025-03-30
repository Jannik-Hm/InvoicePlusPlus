# Invoice++ (InvoicePlusPlus)

Invoice++ is a simple C++ based tool to generate a PDF Invoice.
The generated Invoice will be saved to your Downloads folder as *invoice_number*.pdf

> [!NOTE]
> Inputs are limited to reasonable lengths. In case you hit these limits, feel free to suggest changes.

## Run on macOS

When a binary has been provided to you, you only need to install `Qt` using `brew install qt`. <br/>
The pdf lib is statically linked into the binary.

## Develop and Build

> [!WARNING]
> The CMake file is designed for development on macOS. <br/>
> For development and build on other platforms, paths might need to be adjusted.

### macOS Setup
Dependency installation:
- libharu <br/> `brew install libharu`
- Qt <br/> `brew install qt`

> [!WARNING]
> The project was developed using CLion, compilation using other IDEs has not been validated

## License information

The license can be found under LICENSE in the Repository root folder.

During the development process, tools such as generative AI (ChatGPT), StackOverflow as well as official documentation have been used as inspiration or to generate certain functions such as the UTF-8 to ANSI string conversion.

I do not take responsibility for any external libraries used.
