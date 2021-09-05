<img align="right" src="docs/pictures/github-logo.png" />

# Tutorial<br/>IAR Build Tools for Linux in a GitHub CI 


This tutorial provides a simple example with general guidelines on how to setup a CI (Continuous Integration) workflow with [IAR Build Tools for Linux][iar-bx-url] alongside [GitHub](https://github.com).

Each of the __IAR Build Tools__ packages requires its specific license. Please feel free to [__contact us__](https://iar.com/about/contact) if you would like to learn how to get access to them.

If you want to be notified in your GitHub inbox about updates to this tutorial, you can start __watching__ this repository. You can customize which types of notification you want to get. Read more about [notifications](https://docs.github.com/en/github/managing-subscriptions-and-notifications-on-github/setting-up-notifications/about-notifications) and how to [customize](https://docs.github.com/en/github/managing-subscriptions-and-notifications-on-github/setting-up-notifications/about-notifications#customizing-notifications-and-subscriptions) them.

If you end up with a question specifically related to [this tutorial](https://github.com/iarsystems/bx-github-ci), you might be interested in verifying if it was already answered from [earlier questions][repo-old-issue-url]. Or, [ask a new question][repo-new-issue-url] if you could not find any answer for your question.


## Introduction
### Build server
The __build server__ will contain the __IAR Build Tools for Linux__ installed.

It will also use the [GitHub's Actions][gh-actions-url] workflow relying on its [self-hosted runners][gh-shr-url] feature.  This runner will be configured to connect directly to a GitHub [__private__][gh-shr-priv-url] repository containing one or more software projects, clone the repository and then use the __IAR Build Tools for Linux__ to build and analyze these projects.

The private project repository starts with a __master__ branch containing __production code base__. 

### Development workstation
On his workstation, a _developer_ clones the repository to start working on a new feature. For that, he creates a __feature branch__.



A __Developer__ clones the repository with the __`production`__ branch and then create a feature branch named __`dev-<feature-name||bug-fix>`__ containing a new feature or a bug fix. Then he pushes the branch to the _Origin_. This will trigger a __GitHub Action__ to build the project using the __IAR Build Tools__ in a __Self-hosted runner__.

This way we can make sure that a newly developed feature will not break the build. This scheme will improve the project's quality, and it will help the __Project Manager__ in the validation process while deciding which code changes are acceptable _and_ if it does integrate well to the __`production`-grade__ code base.

![](images/bx-shr-devops-flow.png)

## Requirements
For this tutorial, the following will be required:

* __Dev-Machine__: a __Windows 10__ build 1903+ with the following software installed:
   - [__IAR Embedded Workbench for Arm 8.50.6__](https://www.iar.com/arm)
   - [Git for Windows](https://git-scm.com/download/win) (includes _bash_)
 
* __Build-Server__: a __Ubuntu__ v18.04+ with the following software installed:
    - [__IAR build tools for Arm 8.50.6__](https://www.iar.com/about/contact/sales/) (referred as `BXARM`)
 
* [__IAR License Server__][iar-lms2-url] already __up__, loaded with __activated__ `BXARM` licenses and __reachable__ from the __Build-Server__

* __GitHub.com__:
    - A [GitHub account][gh-join-url] (or a [Microsoft Azure account][gh-azure-url])
    - A private GitHub git repository to store the project files
    - A __Developer__
    - A __Project Manager__ (who, for the current purposes, can temporarily assume the role of the __Developer__)

## Prepare the repository
The first part of this tutorial assumes that the __Project Manager__ is already logged into his `https://github.com/<username>` in order to setup a private repository on GitHub. 

Accelerating things a little bit, we are going to re-use this public repository as base template for the new private one since it comes with an __IAR Embedded Workbench workspace__ that the __Developer__ will, later on, be able to experiment with simulating a new feature implementation under a CI/CD paradigm.

* On __GitHub.com__, import [this repository](https://github.com/IARSystems/bx-self-hosted-runners)
    - into a [new private repository](https://github.com/new/import)
    - __Name__ `shr-private`
    - __Privacy__ `Private`
    - Click __Begin import__

* Once the _importing is complete_, a message will show up:
```
"Your new repository '<username>/shr-private' is ready."
```
* Click on that link to the new repository in the message.

* Go to __Settings__ 
> Equivalent URL: `https://github.com/<username>/shr-private/settings`

* And then __Actions__ 
> Equivalent URL: `https://github.com/<username>/shr-private/settings/actions`

* On the bottom of the page, click __`Add Runner`__
> Equivalent URL: `https://github.com/<username>/shr-private/settings/actions/add-new-runner`

* For __Operating System__ 
   - Select `Linux`

* For __Architecture__ 
   - Select `x64`
          
## Setup the Self-hosted runner
The __Project Manager__ should access the __Build-Server__ to perform the following setup:

### Install the IAR Build Tools for Linux
Install the IAR Build Tools for Linux.

>:warning: Follow the instructions and recommendations of the product's User Guide that comes with the product.

Additionally, it is possible to add the __IAR Build Tools__ directories containing the executables to the search `PATH`, so they can be executed from anywhere.
For example, paste the snippet below to the user's `$HOME/.profile` (or else the `$HOME/.bashrc`) file:
```sh
if [ -d "/opt/iarsystems/bx<arch>" ]; then
  PATH="/opt/iarsystems/bx<arch>/<arch>/bin:/opt/iarsystems/bx<arch>/common/bin:$PATH"
fi
```

Then update the `bx<arch>` in all the paths so they match the product you are using and save the file.

Source the file you modified for the changes to take effect:
For example, 
```
source ~/.profile
```

### Configure the GitHub Actions runner
Then follow the GitHub's instructions for...

* __Download__

and

* __Configure__

...your self-hosted runner, using its default configurations.

> __Tip__
> * You can move the mouse pointer to each desired line in the sequence and click on the __clipboard icon__ to copy it to the clipboard and then paste it to the terminal of your __Build-Server__.

Once you have it configurated, the Actions configuration page (`https://github.com/<username>/shr-private/settings/actions`) should show the __Self-hosted runner__ as `Idle`:
![](images/shr-idle.png)

## Develop the project
As soon as the preliminary setup is done, the __Project Manager__ can notify the __Developer__ about the new private repository for the project's CI/CD workflow.

And then, on the __Dev-Machine__, the __Developer__ will perform the following:

* Launch __Bash for Git__ and then:
```sh
# Clone the "shr-private" repository
$ git clone https://github.com/<username>/shr-private.git

# Change to the repository directory
$ cd shr-private

# Checkout a new branch named "dev-component2-improvement"
$ git checkout -b  dev-component2-improvement
```
> __Note__
> * This repository comes prepared with a __GitHub Action [workflow](https://docs.github.com/en/free-pro-team@latest/actions/reference/workflow-syntax-for-github-actions)__ configurated in the [bxarm.yml](.github/workflows/bxarm.yml) file to build all the 3 projects.

* Launch the __IAR Embedded Workbench for Arm 8.50.6__ and
   - Go to `File` → `Open Workspace...` and select the `workspace.eww` file inside the [workspace](workspace) folder. On the __Workspace__ window, the __`library`__ project should show up __highlighted__ as the active project. 
   - Right-click on the __`library`__ project and choose `Make` (or <kbd>F7</kbd>). The `library` project should build with no errors.
   - Now right-click on the `component2` project and __Set as Active__.
   - Unfold the __`component2`__ project tree and double click on its [main.c](workspace/component2/main.c) file so it will open in the __Code Editor__.
   - Right-click on __`component2`__ and choose `Make` (or <kbd>F7</kbd>). The `component2` project should build with no errors.

### Changing the code for `component2` project 

Now the __Developer__ will start to work on the `dev-component2-improvement` and, for some reason the `DATATYPE` used in `component2` had to change from `uint16_t` to __`float`__ to hold values greater than `0xFFFF`.

* On the [main.c](workspace/component2/main.c) file, right-click on the line with the __[`#include "library.h"`](workspace/component2/main.c#L12)__ and choose __Open "library.h"__.

* In the [library.h](workspace/library/library.h) file, find the line __[`#define DATATYPE uint16_t`](workspace/library/library.h#L19)__ and replace it with
```c
#define DATATYPE float
```

* Now rebuild the `library` project
   - Right-click on `library` and choose `Make` (or <kbd>F7</kbd>). It should build with no errors.

* And then rebuild the `component2` project
   - Right-click on `component2` and choose `Make` (or <kbd>F7</kbd>). It should build with no errors.

Back to the __Git Bash__

* Commit to the changes to the cloned `shr-private` repository
```sh
# Stage the modified file for commit
$ git add workspace/library/library.h

# Commit the changes to the local "shr-private" repository
$ git commit -m "Component 2 improvement proposal"
```

* The expected output is similar to this, but with a different commit hash:
> ```
> [dev-component2-improvement e167db8] Component 2 improvement proposal
> 1 file changed, 1 insertion(+), 1 deletion(-)
> ```

* Finally `push` the code changes back to the `origin` repository:
```sh
$ git push -u origin dev-component2-improvement
```

The expected output is similar to:
> ```
> Enumerating objects: 9, done.
> Counting objects: 100% (9/9), done.
> Delta compression using up to 8 threads
> Compressing objects: 100% (5/5), done.
> Writing objects: 100% (5/5), 1.07 KiB | 363.00 KiB/s, done.
> Total 5 (delta 4), reused 0 (delta 0), pack-reused 0
> remote: Resolving deltas: 100% (4/4), completed with 4 local objects.
> remote:
> remote: Create a pull request for 'dev-component2-improvement' on GitHub by visiting:
> remote:      https://github.com/<username>/shr-private/pull/new/dev-component2-improvement
> remote:
> To github.com:<username>/shr-private.git
>  * [new branch]      dev-component2-improvement -> dev-component2-improvement
> Branch 'dev-component2-improvement' set up to track remote branch 'dev-component2-improvement' from 'origin'.
> ```
   
## Creating a Pull Request
Then it is time for the __Developer__ to go back to __GitHub.com__:

* Go to `https://github.com/<username>/shr-private` and notice that there is a new yellow bar saying that
![](images/pr-compare.png)

* Click `Compare & pull request`

* Here, GitHub will give the __Developer__ the opportunity to write the rationale for the `component2` improvement proposal so the __Project Manager__ can have a better picture of what is going on
![](images/pr-rationale.png)

* Once ready, click `Create pull request`

> __Tip__
> * Follow the link to learn more [About pull requests](https://docs.github.com/en/free-pro-team@latest/github/collaborating-with-issues-and-pull-requests/about-pull-requests)


## Reviewing the Pull Request
It is time for the __Project Manager__ to start [reviewing the pull request](https://docs.github.com/en/free-pro-team@latest/github/collaborating-with-issues-and-pull-requests/approving-a-pull-request-with-required-reviews) which was proposed by the __Developer__ containing the new feature.

Our basic GitHub Actions workflow file bxarm.yml will trigger every time a new feature branch goes through a pull request.

Once it is triggered, it will use the __IAR Build Tools__ installed in the __Build Server__ alongside the runner deamon listening for new jobs.

If a __Developer__ created something new that breaks the build, it will fail the automated verification, warn the __Project Manager__ about the breakage and detail the root cause of the failure.
![](images/pr-build-fail.png)

In this case, the author's proposed change to the shared `library` worked nicely for the `component2` but it has broken the `component1` build.

The __Project Manager__ can now contact the author using the `pull request` itself to keep track of any changes, propose alternatives or even fix other components of the project which might had lurking bugs and which no one else noticed for a while.

Over time this practice helps guaranteeing convergence to improved quality of the `production`-grade code base. It also helps avoiding that new features break other parts of a project. Ultimately it builds a development log of the project which, when properly used, can become a solid asset for consistent deliveries as the project evolves.


## Summary
In short, in this tutorial we went through one of the many ways that the [IAR Build Tools for Linux][iar-bx-url] can be used in CI scenarios.
   
The GitHub Actions provides a great and scalable way to manage automation tasks for building, testing and deploying software. 
   
For more tutorials like this, stay tuned on our [GitHub page][gh-iar-url] and the [IAR Build Tools official page][iar-bx-url] and the [Weekly Breakpoint blog][iar-bkpt-url].

<!-- links -->
[iar-bx-url]: https://www.iar.com/bx
[iar-lms2-url]: https://links.iar.com/lms2-server
[iar-bkpt-url]: https://www.iar.com/about/news-and-events/the-weekly-breakpoint-blog/

[gh-join-url]: https://github.com/join
[gh-azure-url]: https://azure.microsoft.com/en-us/products/github/
[gh-shr-url]: https://docs.github.com/en/free-pro-team@latest/actions/hosting-your-own-runners/about-self-hosted-runners 
[gh-shr-priv-url]: https://docs.github.com/en/free-pro-team@latest/actions/hosting-your-own-runners/about-self-hosted-runners#self-hosted-runner-security-with-public-repositories
[gh-iar-url]: https://github.com/IARSystems

[repo-wiki-url]: https://github.com/IARSystems/bx-github-ci
[repo-new-issue-url]: https://github.com/IARSystems/bx-github-ci/issues/new
[repo-old-issue-url]: https://github.com/IARSystems/bx-github-ci/issues?q=is%3Aissue+is%3Aopen%7Cclosed
