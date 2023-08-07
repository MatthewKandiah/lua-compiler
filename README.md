# lua-compiler
Learning exercise - how would you build a Lua compiler? 

Goal:
- originally thought I'd use LLVM to get a lot of functionality easily, but I've struggled to get it building and linking with my project, and tinkering with cmake files is not my idea of fun. Maybe something to come back to one day
- let's try explicitly targeting WASM, if we generate a sensible AST, it should be possible to generate a valid .wat file, then compile to .wasm using wabt, and we can run that using WASI (hopefully 🤞). If nothing else, learning more about WASM will be a plus

Note - cmake makes my head hurt, so I've blindly followed the advice in https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html to set up my project. I've got an executable building and tests running, which I think is probably good enough for my purposes. If I hit any pain points, it's probably worth revisiting and actually thinking about it a little more!

