<img align="right" src="https://avatars.githubusercontent.com/u/583231?s=96&v=4" />

# IAR Build Tools for Arm on GitHub Actions using Linux runners


>[!WARNING]
>The information in this repository is subject to change without notice and does not constitute a commitment by IAR. While it serves as a valuable reference for DevOps Engineers implementing Continuous Integration with IAR Tools, IAR assumes no responsibility for any errors, omissions, or specific implementations.


## Introduction
From a CI/CD perspective, the [IAR Build Tools for Arm](https://iar.com/bxarm) comes with everything you need to build embedded firmware projects from the command line. This tutorial provides a simple example with general guidelines on how to set up a CI/CD pipeline using [GitHub Actions](https://docs.github.com/en/actions) while taking advantage of the so-called [GitHub self-hosted runners][gh-shr-url].

In case you need an introduction on how to get started with GitHub, use [Quickstart](https://docs.github.com/en/get-started).


## Prerequisites
Before you begin, you will need to download and install the following:
- IAR Build Tools for Arm 9.60.2 for Ubuntu 22.04 x64 ([`bxarm-9.60.2.deb`](https://updates.iar.com/?product=BXARM&version=9.60))
   - IAR customers can download it directly from [IAR MyPages](https://iar.my.site.com/mypages). If you do not have a license, [contact sales](https://iar.com/about/contact).

You also will need:
- A GitHub [organization account](https://docs.github.com/en/get-started/learning-about-github/types-of-github-accounts#organization-accounts)
   - or a GitHub [enterprise account](https://docs.github.com/en/get-started/learning-about-github/types-of-github-accounts#enterprise-accounts).


## Quickstart
Under your organization's GitHub account:

- Go to [Import](https://github.com/new/import) repository.
- Fill **Your old repository's clone URL** with this repository's URL.
- Set the **Repository name** as of your liking.
- Make it 🔘 **Private**. [Why?](https://docs.github.com/actions/hosting-your-own-runners/managing-self-hosted-runners/about-self-hosted-runners#self-hosted-runner-security)
- Finally click **Begin import**.

Once the importing process is complete, a message will show up `Your new repository <organization>/<repo> is ready`. The message will provide a link to jump to the new repository.

## GitHub Actions pipeline example
On your private repository, navigate to the [`.github/workflows/bxarm.yml`](.github/workflows/bxarm.yml) workflow file. This file uses the [GitHub-flavored YAML syntax](https://docs.github.com/en/actions/using-workflows/workflow-syntax-for-github-actions) to describe a pipeline containing multiple jobs found in a typical embedded firmware project.

![image](https://github.com/user-attachments/assets/5aedcd2a-d16c-424e-b125-9131279a121c)

Refer to the [`.github/workflows/bxarm.yml`](.github/workflows/bxarm.yml) workflow file for detailed comments.

## Adding runners to the organization
With GitHub Actions is straightforward enabling a self-hosted runner on a Linux build node where the IAR Build Tools for Arm was installed:
- Navigate to your Organization's (`<org>`) settings page to setup a new runner `https://github.com/<org>/settings/actions/runners/new`.
- Select __`Linux`__ as the __Operating System__.
- Select the __`x64`__ __Architecture__.
- Follow the GitHub-provided instructions on the page to download and configure the runner[^1].

![image](https://github.com/user-attachments/assets/69a105be-5d78-4eea-9ac7-fa8104beb3f2)


You can have as many parallel build nodes with runners as your license allows you to. [Contact sales](https://iar.com/about/contact) for expanding your build capacity.


## Summary
This tutorial provided an overview of how to get started with the IAR Build Tools for Arm on GitHub Actions using self-hosted Linux runners. Development teams can immediately benefit from the comprehensive feedback these modern workflows offer, enabling them to quickly build, analyze, test, and deploy with high quality.

[__` Follow us `__](https://github.com/iarsystems) on GitHub to get updates about tutorials like this and more.


## Issues
For technical support contact [IAR Customer Support][url-iar-customer-support].

For questions or suggestions related to this tutorial: try the [wiki][url-repo-wiki] or check [earlier issues][url-repo-issue-old]. If those don't help, create a [new issue][url-repo-issue-new] with detailed information.


[^1]: From the default installation, the runners become available organization-wide, for all its repositories. These can be [grouped and managed](https://docs.github.com/en/actions/hosting-your-own-runners/managing-self-hosted-runners/managing-access-to-self-hosted-runners-using-groups) as desired.

<!-- links -->
[url-iar-customer-support]: https://iar.my.site.com/mypages/s/contactsupport

[iar-bxarm-url]: https://www.iar.com/bxarm

[gh-yaml-doc-url]: https://docs.github.com/en/free-pro-team@latest/actions/reference/workflow-syntax-for-github-actions
[gh-shr-url]: https://docs.github.com/en/free-pro-team@latest/actions/hosting-your-own-runners/about-self-hosted-runners 
[gh-actions-url]: https://docs.github.com/en/actions
[gh-iar-url]: https://github.com/IARSystems

[url-repo]: https://github.com/IARSystems/bx-github-ci
[url-repo-wiki]: https://github.com/IARSystems/bx-github-ci/wiki
[url-repo-issue-new]: https://github.com/IARSystems/bx-github-ci/issues/new
[url-repo-issue-old]: https://github.com/IARSystems/bx-github-ci/issues?q=is%3Aissue+is%3Aopen%7Cclosed
