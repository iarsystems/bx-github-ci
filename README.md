<img align="right" src="https://avatars.githubusercontent.com/u/583231?s=96&v=4" />

# IAR Build Tools for Arm on Linux in GitHub Actions


> __Disclaimer__
> The information provided in this tutorial is subject to change without notice and does not represent a commitment on any part of IAR. While the information contained herein is useful as reference for DevOps Engineers willing to implement CI/CD using IAR Tools, IAR assumes no responsibility for any errors, omissions or particular implementations.


## Introduction
From a CI/CD perspective, the [IAR Build Tools for Arm](https://iar.com/bxarm) comes with everything you need to build embedded firmware projects from the command line. This tutorial provides a simple example with general guidelines on how to set up a CI/CD pipeline using [GitHub Actions](https://docs.github.com/en/actions) while taking advantage of the so-called [GitHub self-hosted runners][gh-shr-url].

In case you need an introduction on how to get started with GitHub, use [Quickstart](https://docs.github.com/en/get-started).


## Prerequisites
Before you begin, you will need to download and install the following:
- IAR Build Tools for Arm 9.50.1 for Ubuntu 22.04 x64 ([`bxarm-9.50.1.deb`](https://updates.iar.com/?product=BXARM&version=9.50))
   - IAR customers can download it directly from [IAR MyPages](https://iar.my.site.com/mypages). If you do not have a license, [contact sales](https://iar.com/about/contact).
- [CMake 3.22+](https://cmake.org/download/) for the Linux x86_64 platform (***optional**)
- A GitHub [organization account](https://docs.github.com/en/get-started/learning-about-github/types-of-github-accounts#organization-accounts)
   - or a GitHub [enterprise account](https://docs.github.com/en/get-started/learning-about-github/types-of-github-accounts#enterprise-accounts).


## Quickstart
Under your organization's GitHub account:

- Go to [Import](https://github.com/new/import) repository.
- Fill **Your old repository's clone URL** with this repository's URL.
- Set the **Repository name** as of your liking.
- Make it 🔘 **Private**. [Why?](gh-shr-priv-url)
- Finally click **Begin import**.

Once the importing process is complete, a message will show up `Your new repository <organization>/<repo> is ready`. The message will provide a link to jump to the new repository.

## GitHub Actions pipeline example
On your private repository, navigate to the [`.github/workflows/bxarm.yaml`](.github/workflows/bxarml.yaml) script. This file uses the [GitHub-flavored YAML syntax](https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions) to describe a pipeline containing multiple jobs found in a typical embedded firmware project.

![image](https://github.com/felipe-iar/bx-github-ci/assets/54443595/3c27634b-3d6b-4407-91e5-7024a5c22c9b)


## Adding runners to the organization
With GitHub Actions is straightforward to enable a self-hosted runner in a build node which has the IAR Build Tools for Arm installed:
- Navigate to your Organization's settings page to setup a new runner `https://github.com/<org>/settings/actions/runner/new`.
- Select __`Linux`__ For __Operating System__.
- Select __`x64`__ for the __Architecture__.
- Follow the instructions provided by GitHub.

> __Note__
> From the default installation, the runners become available organization-wide, for all its repositories. These can be [grouped and managed](https://docs.github.com/en/actions/hosting-your-own-runners/managing-self-hosted-runners/managing-access-to-self-hosted-runners-using-groups) as desired.


### Hot hints
- The instructions provided by GitHub when setting up a new runner will tell you how to `run.sh` the script, which will not survive a reboot. In order to install the runner as a service, refer to this [hint](https://docs.github.com/en/actions/hosting-your-own-runners/managing-self-hosted-runners/configuring-the-self-hosted-runner-application-as-a-service?platform=linux).


## Issues
Found an issue or have a suggestion specifically related to the [__bx-github-ci__][url-repo] tutorial? Feel free to use the public issue tracker.
- Do not forget to take a look at [earlier issues][url-repo-issue-old].
- If creating a [new][url-repo-issue-new] issue, please describe it in detail.


## Summary
This tutorial provided an overview on how to get started with the IAR Build Tools for Arm on Linux in GitHub Actions, from where development teams can immediately benefit from holistic feedbacks these modern workflows provide to quickly build, analyze, test and deploy with quality.

[__` Follow us `__](https://github.com/iarsystems) on GitHub to get updates about tutorials like this and more.

<!-- links -->
[iar-bxarm-url]: https://www.iar.com/bxarm

[gh-yaml-doc-url]: https://docs.github.com/en/free-pro-team@latest/actions/reference/workflow-syntax-for-github-actions
[gh-shr-url]: https://docs.github.com/en/free-pro-team@latest/actions/hosting-your-own-runners/about-self-hosted-runners 
[gh-actions-url]: https://docs.github.com/en/actions
[gh-iar-url]: https://github.com/IARSystems

[url-repo]: https://github.com/IARSystems/bx-github-ci
[url-repo-issue-new]: https://github.com/IARSystems/bx-github-ci/issues/new
[url-repo-issue-old]: https://github.com/IARSystems/bx-github-ci/issues?q=is%3Aissue+is%3Aopen%7Cclosed
