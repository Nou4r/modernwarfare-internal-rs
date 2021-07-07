use std::process::Command;

fn main() {
    let dst = cmake::Config::new("framework")
        .profile("Release")
        .build();

    println!("cargo:rustc-link-search=native={}", dst.display());
    println!("cargo:rustc-link-lib=static=framework");

    // Include build ID
    let output = Command::new("git").args(&["log", "--pretty=format:%h", "-n", "1"]).output().unwrap();
    let git_hash = String::from_utf8(output.stdout).unwrap().replace("\"", "");
    println!("cargo:rustc-env=GIT_HASH={}", git_hash);
}