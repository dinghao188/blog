# I record some skills in this md file

>## 一、关于git的理解
>
>>### 1. *git是什么？特性?*
>>
>>>- Git是一个远程的代码管理仓库，可用于多人协同开发。
>>>- Git分为本地仓库和远程仓库，同一个仓库可以有许多不同的分支，不同分支可以合并，本地仓库提交到远程仓库也是合并的过程。
>>>- 合并之前需要先在本地排除矛盾之后才能正确合并
>>>- 每个commit都是一个时间节点，每个分支都是指向某个节点的指针(如master)，HEAD指针指向当前分支最新的commit。
>>
>>### 2. *Git常用操作？*
>>
>>>- git clone: *将远程仓库克隆到本地*
>>>- git pull: *从远程仓库拉取最新的代码(更新本地仓库，该操作也经常用来合并分支和仓库)*
>>>- git add: *将改动添加到本地仓库*
>>>- git commit: *提交本次改动到本地仓库*
>>>- git push: *提交更新到远程仓库(此操作经常会出现失败，此时需要先pull,然后查看哪些文件存在冲突，正确修正矛盾之后再次add,commit,push)*
>>>- git checkout: *切换分支。-b branch,新建branch分支并切换;-d branch,删除branch分支*
>>>- git merge [branch]: *将branch分支合并到当前分支(必须先pull当前分支)*
>>
>
