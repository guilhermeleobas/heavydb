<#--
 Copyright 2022 HEAVY.AI, Inc.
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
-->

/*
 * Kill either running or pending query using the following syntax:
 *
 * KILL QUERY <querySession>
 */
SqlDdl SqlKillQuery(Span s) :
{
    SqlNode querySession;
}
{
    <KILL> <QUERY>
    querySession = StringLiteral()
    {
        return new SqlKillQuery(s.end(this), querySession.toString());
    }
}

/*
 * Clear CPU or GPU memory
 *
 * ALTER SYSTEM CLEAR CPU|GPU|RENDER MEMORY
 */
SqlDdl SqlAlterSystemClear(Span s) :
{
    String cacheType;
}
{
    <ALTER>
    <SYSTEM>
    <CLEAR>
    (
        <CPU>
        {
            cacheType = "CPU";
        }
    |
        <GPU>
        {
            cacheType = "GPU";
        }
    |
        <RENDER>
        {
            cacheType = "RENDER";
        }
    )
    <MEMORY>
    {
        return new SqlAlterSystemClear(s.end(this), cacheType);
    }
}