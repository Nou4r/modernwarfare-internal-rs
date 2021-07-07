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

    let output = Command::new("git").args(&["rev-parse", "--abbrev-ref", "HEAD"]).output().unwrap();
    let git_branch = String::from_utf8(output.stdout).unwrap().replace("\"", "");

    let output = Command::new("git").args(&["status", "-s"]).output().unwrap();
    let modified = String::from_utf8(output.stdout).unwrap().contains(" ");

    println!("cargo:rustc-env=GIT_BRANCH={}", git_branch);
    println!("cargo:rustc-env=GIT_HASH={}", git_hash);
    println!("cargo:rustc-env=GIT_MODIFIED_STR={}", if modified { " dev" } else { "" });
}