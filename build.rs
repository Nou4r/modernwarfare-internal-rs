fn main() {
    let dst = cmake::build("framework");

    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=static=framework");
}