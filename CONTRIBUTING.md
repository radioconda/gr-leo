# Libre Space Foundation Contribution Guide #

## Table of Contents ##

  * [Introduction](#introduction)
  * [Obtain the source code](#obtain-the-source-code)
  * [Separate the changes](#separate-the-changes)
  * [Quality check of the changes](#quality-check-of-the-changes)
  * [Describe the changes](#describe-the-changes)
  * [Create a merge request](#create-a-merge-request)
  * [Respond to review comments](#respond-to-review-comments)
  * [Don’t get discouraged - or impatient](#dont-get-discouraged-or-impatient)
  * [Sign your work - the Developer’s Certificate of Origin](#sign-your-work-the-developers-certificate-of-origin)
  * [References](#references)

## Introduction ##
For a person or company who wishes to submit a change to a Libre Space Foundation project source code, the process can sometimes be daunting if you’re not familiar with “the system”.
This document is a collection of suggestions which can greatly increase the chances of your change being accepted.
It is based on Linux kernel patch submission guidelines.

## Obtain the source code ##

All Libre Space Foundation projects code is maintained under Git.
Obtain a copy of the source code using `git clone`.
Development usually takes place under `master` or `dev` branch.

## Separate the changes ##

Make changes as small as possible by separating each logical change into a separate commit.
Such commits are also called *atomic*.
Atomic commits must be complete and functional.
Small commits make it easier for someone to review by seeing changes incrementally.
It also makes it easier to roll back changes without affecting other changes.

For example, if your changes include both bug fixes and a new feature, separate those changes into two or more commits.
On the other hand, if you make a single change to numerous files, group those changes into a single commit.
Thus a single logical change is contained within a single commit.
The point to remember is that each commit should make an easily understood change that can be verified by reviewers.
Each commit should be justifiable on its own merits.

When creating a merge request from a series of commits, take special care to ensure that the software builds and runs properly after each commit in the series.
Developers using `git bisect` to track down a problem can end up splitting your merge request at any point; they will not thank you if you introduce bugs in the middle.

If you cannot condense your merge request into a smaller set of commits, then only submit say 15 or so at a time and wait for review and integration.

Never commit binary files.
Once they are part of Git repository history they cannot be removed.

## Quality check of the changes ##

Continuous Integration will check your changes automatically once you create a merge request.
Nevertheless, local quality check should also be done before submitting a merge request.
The checks can include:
  * Static code analysis and coverage
  * Dynamic code analysis
  * Unit testing
  * Functional testing

All quality checks must pass for your changes to be merged.

## Describe the changes ##

These are the seven rules of a great Git commit messages:

  * Separate subject from body with a blank line
  * Limit the subject line to 50 characters (if possible)
  * Capitalize the subject line
  * Do not end the subject line with a period
  * Use the imperative mood in the subject line
  * Wrap the body at 72 characters
  * Use the body to explain what and why vs. how

See [How to Write a Git Commit Message](https://chris.beams.io/posts/git-commit/) by Chris Beams for details.

Try to solve a single problem per each commit.
If your description ends up too long, that’s an indication that you probably need to split up your commit.
See [Separate the changes](#separate-the-changes).

Create commit or merge requests descriptions that are self-contained.
This benefits both the maintainers and reviewers.
Always use your real name and e-mail address for committing changes.

If the commit fixes a reported issue, refer to that bug entry by issue number.
The issue will be closed automatically after merge, if it matches [this regular expression](https://docs.gitlab.com/ce/user/project/issues/automatic_issue_closing.html).

## Create a merge request ##

A series of loosely related commits can be submitted as a merge request.
Libre Space Foundation projects follow a [forking workflow](https://docs.gitlab.com/ce/workflow/forking_workflow.html).
Merge requests must not contain other merge requests; re-base your commits if necessary.

## Respond to review comments ##

Your merge request will almost certainly get comments from reviewers on ways in which it can be improved.
You must respond to those comments; ignoring reviewers is a good way to get ignored in return.
Be sure to tell the reviewers what changes you are making and to thank them for their time.
Code review is a tiring and time-consuming process, and reviewers sometimes get grumpy.
Even in that case, though, respond politely and address the problems they have pointed out.

## Don’t get discouraged - or impatient ##

After you have submitted your merge request, be patient and wait.
Reviewers are busy people and may not get to your merge request right away.
You should receive comments within a week or so.
Wait for a minimum of one week before pinging reviewers - possibly longer during busy times.

## Sign your work - the Developer’s Certificate of Origin ##

To improve tracking of who did what, especially with commits that can percolate to their final resting place in Libre Space Foundation projects code-base through several layers of maintainers, we’ve introduced a “sign-off” procedure on commits.

The sign-off is a simple line at the end of the explanation for the commit, which certifies that you wrote it or otherwise have the right to pass it on as an open-source patch.
The rules are pretty simple:

if you can certify the below:

    Developer’s Certificate of Origin 1.1
    
    By making a contribution to this project, I certify that:
    
    a. The contribution was created in whole or in part by me and I have
	   the right to submit it under the open source license indicated in
	   the LICENSE file; or
    b. The contribution is based upon previous work that, to the best of
	   my knowledge, is covered under an appropriate open source license
	   and I have the right under that license to submit that work with
	   modifications, whether created in whole or in part by me, under
	   the same open source license (unless I am permitted to submit
	   under a different license), as indicated in the LICENSE file; or
    c. The contribution was provided directly to me by some other person
	   who certified (a), (b) or (c) and I have not modified it.
    d. I understand and agree that this project and the contribution are
	   public and that a record of the contribution (including all
	   personal information I submit with it, including my sign-off) is
	   maintained indefinitely and may be redistributed consistent with
	   this project or the open source license(s) involved.

then you just add a line saying:

`Signed-off-by: Random J Developer <random@developer.example.org>`

using your real name (sorry, no pseudonyms or anonymous contributions.)

If you are a maintainer, sometimes you need to slightly modify commits order to merge them.
If you stick strictly to rule (c), you should ask the submitter to rediff, but this is a totally counter-productive waste of time and energy.
Rule (b) allows you to adjust the code, but then it is very impolite to change one submitter’s code and make him endorse your bugs.
To solve this problem, it is recommended that you add a line between the last Signed-off-by header and yours, indicating the nature of your changes.
While there is nothing mandatory about this, it seems like prepending the description with your mail and/or name, all enclosed in square brackets, is noticeable enough to make it obvious that you are responsible for last-minute changes. Example:

```
Signed-off-by: Random J Developer <random@developer.example.org>
[lucky@maintainer.example.org: struct foo moved from foo.c to foo.h]
Signed-off-by: Lucky K Maintainer <lucky@maintainer.example.org>
```

## References ##

  * Linux kernel documentation - [Submitting patches: the essential guide to getting your code into the kernel](https://www.kernel.org/doc/html/latest/process/submitting-patches.html)
