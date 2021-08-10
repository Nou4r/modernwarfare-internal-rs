#![feature(exit_status_error)]

use std::process::Command;

fn parse_offsets(header: &str) -> String {
    let i = header.find("constexpr").unwrap();
    let j = header.match_indices('}').last().unwrap().0;
    let str = header[i..j].to_string();
    let re = regex::Regex::new(r"constexpr auto (\w*) = (\w*);").unwrap();
    re.replace_all(&str, |cap: &regex::Captures| {
        format!("pub const {}: u64 = {};", &cap[1].to_uppercase(), &cap[2])
    }).to_string().replace("namespace", "pub mod")
}

fn main() {
    let args = ["framework/Framework.sln", "/property:Configuration=RustLib", "/property:Platform=x64"];

    let mut cmd = Command::new("C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/MSBuild/Current/Bin/amd64/MSBuild.exe");

    #[cfg(feature = "klar")]
    cmd.env("ExternalCompilerOptions", "/DKLAR");

    cmd
        .args(&args)
        .status()
        .unwrap()
        .exit_ok()
        .expect("Failed to compile Framework.sln");

    println!("cargo:rustc-link-search=native=framework/x64/RustLib");
    println!("cargo:rustc-link-lib=static=Framework");

    let offsets = parse_offsets(&std::fs::read_to_string("framework/Offsets.h").unwrap());
    std::fs::write("src/generated.rs", offsets).unwrap();

    // Include build ID
    let output = Command::new("git").args(&["log", "--pretty=format:%h", "-n", "1"]).output().unwrap();
    let git_hash = String::from_utf8(output.stdout).unwrap().replace("\"", "");

    let output = Command::new("git").args(&["rev-parse", "--abbrev-ref", "HEAD"]).output().unwrap();
    let git_branch = String::from_utf8(output.stdout).unwrap().replace("\"", "");

    let output = Command::new("git").args(&["status", "-s"]).output().unwrap();
    let modified = String::from_utf8(output.stdout).unwrap().contains('M');

    println!("cargo:rustc-env=GIT_BRANCH={}", git_branch);
    println!("cargo:rustc-env=GIT_HASH={}", git_hash);
    println!("cargo:rustc-env=GIT_MODIFIED_STR={}", if modified { "*" } else { "" });
}